#include "instance.h"
#include "../core/objects.h"
#include "directx/directx.h"
#include "interface/interface.h"
#include "../tools/timeobject.h"
#include "../tools/xorstr.h"
#include "../tools/util.h"

typedef HRESULT(WINAPI* PFN_GetDpiForMonitor)(HMONITOR, int, UINT*, UINT*);
float GetDpiScaleForMonitor(void* monitor)
{
    UINT xdpi = 96, ydpi = 96;

        static HINSTANCE shcore_dll = ::LoadLibraryA(skCrypt("shcore.dll"));
        static PFN_GetDpiForMonitor GetDpiForMonitorFn = nullptr;
        if (GetDpiForMonitorFn == nullptr && shcore_dll != nullptr)
            GetDpiForMonitorFn = (PFN_GetDpiForMonitor)GetProcAddress(shcore_dll, skCrypt("GetDpiForMonitor"));
        if (GetDpiForMonitorFn != nullptr)
        {
            GetDpiForMonitorFn((HMONITOR)monitor, 0, &xdpi, &ydpi);
            return xdpi / 96.0f;
        }
   
    const HDC dc = ::GetDC(nullptr);
    xdpi = ::GetDeviceCaps(dc, LOGPIXELSX);
    ydpi = ::GetDeviceCaps(dc, LOGPIXELSY);
    ::ReleaseDC(nullptr, dc);

    return xdpi / 96.0f;
}

float GetDpiScaleForHwnd(void* hwnd)
{
    HMONITOR monitor = ::MonitorFromWindow((HWND)hwnd, MONITOR_DEFAULTTONEAREST);
    return GetDpiScaleForMonitor(monitor);
}

DWORD NTAPI WindowCallback(TWinInstance* Instance)
{   
    Instance->hMainWindow = ::CreateWindowW(Instance->InstanceInformation->hWinClass.lpszClassName,
        Instance->InstanceInformation->hWinClass.lpszClassName, Instance->InstanceInformation->dwStyle,
        Instance->InstanceInformation->x1, Instance->InstanceInformation->y1, Instance->InstanceInformation->x2, Instance->InstanceInformation->y2,
        HWND_DESKTOP, NULL, Instance->InstanceInformation->hWinClass.hInstance, NULL);

    SetWindowLong(Instance->hMainWindow, Instance->InstanceInformation->GwStyleIndex, Instance->InstanceInformation->GwStyleNewLong);

    if (Instance->InstanceInformation->ExtendDwm)
    {
        MARGINS margin = { -1 };
        DwmExtendFrameIntoClientArea(Instance->hMainWindow, &margin);
    }

    RECT Rect;
    GetClientRect(Instance->hMainWindow, &Rect);

    D2D1_SIZE_U size = D2D1::SizeU(
        Rect.right - Rect.left,
        Rect.bottom - Rect.top);

    Instance->InstanceInformation->x2 = size.width;
    Instance->InstanceInformation->y2 = size.height;

    Instance->DirectXInstance = new CD2D1Render;
    Instance->DirectXInstance->Construct(Instance->hMainWindow, Instance->InstanceInformation->bUseVsync);

    Instance->InterfaceInstance = new TInterfaceInstance;
    Instance->InterfaceInstance->Create(Instance , TVector2D(Instance->InstanceInformation->x2, Instance->InstanceInformation->y2));

    ::ShowWindow(Instance->hMainWindow, SW_SHOWDEFAULT);
    ::UpdateWindow(Instance->hMainWindow);

    while (true)
    {
        bool bCheckForDestruction = Instance->CheckForThreadInstanceBool();

        if (bCheckForDestruction) {
            std::unique_lock<std::shared_mutex> Lock(Instance->Mutex);
            Instance->bDestroyInstance = false;
            return 0;
        }
   
        MSG msg;
        while (::PeekMessage(&msg, Instance->hMainWindow, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);

            if (msg.message == WM_QUIT)
                break;

        }

        if (Instance->flDpiScaling < 0.0f) 
            Instance->flDpiScaling = GetDpiForWindow(Instance->hMainWindow);

        Instance->DirectXInstance->BeginScene();

        Instance->InterfaceInstance->PreRenderCallback(Instance);

        Instance->Callback(Instance);

        Instance->InterfaceInstance->PostRenderCallback(Instance);

        Instance->DirectXInstance->EndScene();

        Instance->iTickCount += 1;

    }

    return 0;
}

bool TWinInstance::Setup(FnRenderCallback _Callback,WNDPROC hWinProc, std::wstring szWindowName, 
    DWORD dwStyle, DWORD x1, DWORD y1, DWORD x2, DWORD y2, int GwStyleIndex, LONG GwStyleNewLong, bool ExtendDwm, bool bUseVsync) {

    if (!_Callback)
        return false;

    float flOriginalDpiScale = GetDpiScaleForHwnd(GetDesktopWindow());

    float flScaledWidth = x2 * flOriginalDpiScale;
    float flScaledHeight = y2 * flOriginalDpiScale;

    InstanceInformation = new TCreateInstanceInfo;

    InstanceInformation->dwStyle = dwStyle;
    InstanceInformation->x1 = x1;
    InstanceInformation->y1 = y1;
    InstanceInformation->x2Original = x2;
    InstanceInformation->y2Original = y2;
    InstanceInformation->x2 = flScaledWidth;
    InstanceInformation->y2 = flScaledHeight;
    InstanceInformation->ExtendDwm = ExtendDwm;
    InstanceInformation->GwStyleIndex = GwStyleIndex;
    InstanceInformation->GwStyleNewLong = GwStyleNewLong;
    InstanceInformation->bUseVsync = bUseVsync;

    Callback = _Callback;

    InstanceInformation->hWinClass.lpszClassName = szWindowName.c_str();                           InstanceInformation->hWinClass.lpfnWndProc = hWinProc;
    InstanceInformation->hWinClass.cbSize = sizeof(WNDCLASSEX);                          InstanceInformation->hWinClass.style = CS_VREDRAW | CS_HREDRAW;
    InstanceInformation->hWinClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);                InstanceInformation->hWinClass.hInstance = NULL;
    InstanceInformation->hWinClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);             InstanceInformation->hWinClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    InstanceInformation->hWinClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);   InstanceInformation->hWinClass.cbWndExtra = 12;
    InstanceInformation->hWinClass.lpszMenuName = NULL;                                   InstanceInformation->hWinClass.cbClsExtra = 0;

    ::RegisterClassExW(&InstanceInformation->hWinClass);
    
    return true;
}

void TWinInstance::LockAndSetDestroyInstanceBool() {

    std::unique_lock<std::shared_mutex> Lock(Mutex);

    bDestroyInstance = true;
}

bool TWinInstance::CheckForThreadInstanceBool()
{
    std::unique_lock<std::shared_mutex> Lock(Mutex);

    return bDestroyInstance;
}

void TWinInstance::WaitAndDestroyInstanceThread() {
   
    LockAndSetDestroyInstanceBool();

    while (CheckForThreadInstanceBool())
    {
        Sleep(1);
    }
}

void TWinInstance::Destroy() {

    WaitAndDestroyInstanceThread();

    ::DestroyWindow(hMainWindow);
    ::UnregisterClassW(InstanceInformation->hWinClass.lpszClassName, InstanceInformation->hWinClass.hInstance);

    if (DirectXInstance) 
        delete DirectXInstance;

    if (InterfaceInstance) {
        InterfaceInstance->OnDestruction();
        delete InterfaceInstance;
    }

}


TWinInstance* TInstanceManager::CreateTransparentInstance(FnRenderCallback _Callback, std::wstring szWindowName, DWORD x2, DWORD y2, bool bUseVsync, int x1, int y1)
{
   return TObjects::GInstanceManager->CreateInstance(_Callback, szWindowName, x1, y1, x2, y2, WS_POPUP, GWL_EXSTYLE, WS_EX_TOOLWINDOW, true, bUseVsync);
}

LRESULT WINAPI WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
TWinInstance* TInstanceManager::CreateInstance(FnRenderCallback _Callback, std::wstring szWindowName, int x1, int y1, DWORD x2, DWORD y2, DWORD dwStyle, int GwStyleIndex, LONG GwStyleNewLong, bool ExtendDwm,bool bUseVsync) {

    if (!_Callback)
        return nullptr;

    TWinInstance** WinInstance = arrInstances.AddBack(new TWinInstance());
   
    if (!WinInstance)
        return nullptr;

    TWinInstance* Instance = *WinInstance;
    
    if (!Instance)
        return nullptr;

    float flDpiScale = GetDpiScaleForHwnd(GetDesktopWindow());

    RECT WindowRect;
    GetWindowRect(GetDesktopWindow(), &WindowRect);

    float flScaledWidth = x2 * flDpiScale;
    float flScaledHeight = y2 * flDpiScale;

    Instance->Setup(_Callback, WindowProc, szWindowName, dwStyle, x1 == -1 ? ((WindowRect.right / 2.f) - (flScaledWidth / 2.f)) : x1, y1 == -1 ? (WindowRect.bottom / 2.f) - (flScaledHeight / 2.f) : y1, x2, y2, GwStyleIndex, GwStyleNewLong, ExtendDwm, bUseVsync);

    TUtilities::CreateThread(WindowCallback, Instance);

    return Instance;
}

void TInstanceManager::DestroyInstance(TWinInstance* Instance) 
{
    if (arrInstances.IsEmpty())
        return;

    for (int iCurrent = 0; iCurrent < arrInstances.ArraySize(); iCurrent++) {
        if (*arrInstances[iCurrent] == Instance) {
            (*arrInstances[iCurrent])->Destroy();
            delete *arrInstances[iCurrent];
            arrInstances.PopAt(iCurrent);
        }
    }

}

TWinInstance* TInstanceManager::FindInstanceInList(HWND Window) {

    if (arrInstances.IsEmpty())
        return nullptr;

    for (int iCurrent = 0; iCurrent < arrInstances.ArraySize(); iCurrent++)
        if ((*arrInstances[iCurrent])->hMainWindow == Window)
            return *arrInstances[iCurrent];
    
    return nullptr;
}

LRESULT WINAPI WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
    TWinInstance* CurrentInstance = TObjects::GInstanceManager->FindInstanceInList(hWnd);

    if (!CurrentInstance)
        return ::DefWindowProc(hWnd, msg, wParam, lParam);

    switch (msg)
    {
    case WM_MOUSEACTIVATE:
        return 0;
    case WM_NCACTIVATE:
        return 0;
    case WM_ACTIVATEAPP:
        return 0;
    case WM_SIZE:
    {
        if (wParam != SIZE_MINIMIZED) {

            if (CurrentInstance->DirectXInstance->RenderTarget != NULL)
               CurrentInstance->DirectXInstance->RenderTarget->Resize(D2D1_SIZE_U((UINT)LOWORD(lParam), (UINT)HIWORD(lParam)));

            if (CurrentInstance->InterfaceInstance != NULL)
                CurrentInstance->InterfaceInstance->Resize(TVector2D((UINT)LOWORD(lParam), (UINT)HIWORD(lParam)));

        }

        if (CurrentInstance->InterfaceInstance)
            CurrentInstance->InterfaceInstance->OnWinProc(CurrentInstance, hWnd, msg, wParam, lParam);

        return 0;
    }
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU)
            return 0;
        break;
    case WM_ERASEBKGND:
        return 0;
    case WM_DESTROY: {
        ::PostQuitMessage(0);
        return 0;
    }
    }

    if (CurrentInstance->InterfaceInstance)
        CurrentInstance->InterfaceInstance->OnWinProc(CurrentInstance, hWnd, msg, wParam, lParam);

    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
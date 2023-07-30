#pragma once

#include "../core/core.h"

#include <d3d11.h>
#include <dwmapi.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>

#pragma comment( lib, "dwrite" )
#pragma comment( lib, "d2d1" )
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"dwmapi.lib")

#include "../tools/array.h"

#define GetDpiScaledValue(Scale , Value) Value * Scale / 96.f
#define GetDpiUnscaledValue(Scale , RelativeValue) RelativeValue / (Scale / 96.f) 

class CD2D1Render;
class TWinInstance;
class TInterfaceInstance;

#define MAX_WINDOW_INSTANCES 500

using FnRenderCallback = void(*)(TWinInstance*);

struct TCreateInstanceInfo {
    DWORD dwStyle;
    DWORD x1; 
    DWORD y1; 
    DWORD x2; 
    DWORD y2; 
    DWORD x2Original;
    DWORD y2Original;
    bool bUseVsync = false;
    bool ExtendDwm; 
    int GwStyleIndex; 
    LONG GwStyleNewLong;
    WNDCLASSEXW hWinClass;
};

class TWinInstance {
public:

    TWinInstance() {

    }

    ~TWinInstance()
    {
        Destroy();
    }

    bool Setup(FnRenderCallback _Callback, WNDPROC hWinProc, std::wstring szWindowName, DWORD dwStyle, DWORD x1, DWORD y1, DWORD x2, DWORD y2, int GwStyleIndex, LONG GwStyleNewLong, bool ExtendDwm , bool bUseVsync);
    void Destroy();

    bool CheckForThreadInstanceBool();
private:
    void WaitAndDestroyInstanceThread();
    void LockAndSetDestroyInstanceBool();
public:
    __int64 iTickCount = 0;
    float flDpiScaling = -1.0f;
    float flOriginalDpiScale = 0.0f;
    TCreateInstanceInfo* InstanceInformation;
    FnRenderCallback Callback;
    HWND hMainWindow = NULL;
    CD2D1Render* DirectXInstance = nullptr;
    TInterfaceInstance* InterfaceInstance = nullptr;
    bool bDestroyInstance = false;
    std::shared_mutex Mutex;
};


class TInstanceManager {
public:
    TWinInstance* CreateTransparentInstance(FnRenderCallback _Callback, std::wstring szWindowName, DWORD x2, DWORD y2, bool bUseVsync = true, int x1 = -1, int y1 = -1);

    TWinInstance* CreateInstance(FnRenderCallback _Callback, std::wstring szWindowName, int x1, int y1, DWORD x2, DWORD y2, DWORD dwStyle, int GwStyleIndex, LONG GwStyleNewLong, bool ExtendDwm = false, bool bUseVsync = true);
    void DestroyInstance(TWinInstance* Instance);
    TWinInstance* FindInstanceInList(HWND Window);
private:
    TArray<TWinInstance*, MAX_WINDOW_INSTANCES> arrInstances;
};


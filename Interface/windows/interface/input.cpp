#include "input.h"

bool TInputSystem::IsKeyToggled(int VirtualKey)
{
    return bKeyToggle[VirtualKey];
}

bool TInputSystem::IsKeyClicked(int VirtualKey) {
    return bKeyClicked[VirtualKey];
}

bool TInputSystem::IsKeyDownRaw(int VirtualKey) {
    return bKeyDownRaw[VirtualKey];
}

bool TInputSystem::IsKeyDown(int VirtualKey)
{
    return bKeyDown[VirtualKey];
}

bool TInputSystem::IsMouseMoveInputReceived() {
    return bMouseUpdateReceived;
}

bool TInputSystem::IsPointInsideRegion(TVector2D& vecPoint, TVector2D& vecMin, TVector2D& vecMax)
{
    if (vecPoint.x >= vecMin.x && vecPoint.y >= vecMin.y && vecPoint.x <= vecMax.x && vecPoint.y <= vecMax.y)
        return true;

    return true;
}

bool TInputSystem::IsCursorInsideRegionRelative(const TVector2D& vecRegionRelativePosition, const TVector2D& vecRegionSize, bool bIgnoreY , bool bIgnoreX )
{
    if (!bCursorInsideWindow)
        return false;

    if (!bIgnoreX)
        if (vecMousePosition.x < vecRegionRelativePosition.x || vecMousePosition.x >(vecRegionRelativePosition.x + vecRegionSize.x) )
            return false;
    
    if (!bIgnoreY)
        if (vecMousePosition.y < vecRegionRelativePosition.y || vecMousePosition.y >(vecRegionRelativePosition.y + vecRegionSize.y))
            return false;
    
    return true;
}

std::string* TInputSystem::GetRecentKeyInput() {
    return &RecentKeyInput;
}

bool TInputSystem::IsCursorInsideWindow() {
    return bCursorInsideWindow;
}

bool TInputSystem::IsMouseMoveInputReceivedDesktop() {
    return bDesktopMouseUpdateReceived;
}

void TInputSystem::InputStart() {

    POINT CurrentPoint;
    GetCursorPos(&CurrentPoint);

    if (CurrentPoint.x != vecDesktopMousePosition.x || vecDesktopMousePosition.y != CurrentPoint.y) {
        vecDesktopMousePositionDelta = TVector2D(CurrentPoint.x - vecDesktopMousePosition.x, CurrentPoint.y - vecDesktopMousePosition.y);
        vecDesktopMousePosition = TVector2D(CurrentPoint.x, CurrentPoint.y);
        bDesktopMouseUpdateReceived = true;
    }

}

void TInputSystem::InputFinished() {

    bDesktopMouseUpdateReceived = false;
    bMouseUpdateReceived = false;

    RtlZeroMemory(bKeyClicked,sizeof bKeyClicked);
    RtlZeroMemory(bKeyDownRaw, sizeof bKeyDownRaw);
    RecentKeyInput.clear();
}

void TInputSystem::OnWinProc(TWinInstance* WinInstance , HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{

    switch (msg)
    {
    case WM_MOUSEMOVE:
    {
        if (!bCursorInsideWindow)
        {
            TRACKMOUSEEVENT TrackEvent = { sizeof(TrackEvent), TME_LEAVE, hWnd, 0 };
            ::TrackMouseEvent(&TrackEvent);
            bCursorInsideWindow = true;
        }

        POINT MousePosition = { (LONG)GET_X_LPARAM(lParam), (LONG)GET_Y_LPARAM(lParam) };

        vecMousePositionDelta = TVector2D( MousePosition.x - vecMousePosition.x, MousePosition.y - vecMousePosition.y);
        vecMousePosition = TVector2D(MousePosition.x, MousePosition.y);
        
        vecMousePosition.x = GetDpiUnscaledValue(WinInstance->flDpiScaling, vecMousePosition.x);
        vecMousePosition.y = GetDpiUnscaledValue(WinInstance->flDpiScaling, vecMousePosition.y);

        bMouseUpdateReceived = true;

        break;
    }
    case WM_MOUSELEAVE: {
        bCursorInsideWindow = false;
        vecMousePosition = TVector2D(-1,-1);
        vecMousePositionDelta = TVector2D(-1, -1);
        bKeyDown[VK_LBUTTON] = false;
        bKeyDown[VK_RBUTTON] = false;
        bKeyDown[VK_MBUTTON] = false;
        break;
    }
    case WM_LBUTTONUP:
    case WM_LBUTTONDOWN:
    {
        bKeyDown[VK_LBUTTON] = msg == WM_LBUTTONDOWN;
        
        if (bKeyDown[VK_LBUTTON])
            bKeyDownRaw[VK_LBUTTON] = true;

        if (bKeyDown[VK_LBUTTON] && !bPrevKeyDown[VK_LBUTTON])
            bKeyToggle[VK_LBUTTON] = !bKeyToggle[VK_LBUTTON];
       
        if (bPrevKeyDown[VK_LBUTTON] != bKeyDown[VK_LBUTTON])
          bKeyClicked[VK_LBUTTON] = bKeyDown[VK_LBUTTON];

        bPrevKeyDown[VK_LBUTTON] = bKeyDown[VK_LBUTTON];
        break;
    }
    case WM_RBUTTONUP:
    case WM_RBUTTONDOWN:
    {     
        bKeyDown[VK_RBUTTON] = msg == WM_RBUTTONDOWN;
       
        if (bKeyDown[VK_RBUTTON])
            bKeyDownRaw[VK_RBUTTON] = true;

        if (bKeyDown[VK_RBUTTON] && !bPrevKeyDown[VK_RBUTTON])
            bKeyToggle[VK_RBUTTON] = !bKeyToggle[VK_RBUTTON];
       
        if (bPrevKeyDown[VK_RBUTTON] != bKeyDown[VK_RBUTTON])
            bKeyClicked[VK_RBUTTON] = bKeyDown[VK_RBUTTON];

        bPrevKeyDown[VK_RBUTTON] = bKeyDown[VK_RBUTTON];
        break;
    }
    case WM_MBUTTONUP:
    case WM_MBUTTONDOWN:
    {
        bKeyDown[VK_MBUTTON] = msg == WM_MBUTTONDOWN;
      
        if (bKeyDown[VK_MBUTTON])
            bKeyDownRaw[VK_MBUTTON] = true;

        if (bKeyDown[VK_MBUTTON] && !bPrevKeyDown[VK_MBUTTON])
            bKeyToggle[VK_MBUTTON] = !bKeyToggle[VK_MBUTTON];
     
        if (bPrevKeyDown[VK_MBUTTON] != bKeyDown[VK_MBUTTON])
            bKeyClicked[VK_MBUTTON] = bKeyDown[VK_MBUTTON];

        bPrevKeyDown[VK_MBUTTON] = bKeyDown[VK_MBUTTON];
        break;
    }
    case WM_CHAR:
    {                  
        RecentKeyInput.append(1, (char)wParam);
        break;
    }
    case WM_KEYDOWN:
    case WM_KEYUP:
    case WM_SYSKEYDOWN:
    case WM_SYSKEYUP:
    {
        int vk = (int)wParam;

        if (vk < 256)
        {
      
            if (msg == WM_KEYUP || msg == WM_SYSKEYUP)
                bKeyDown[vk] = false;
            else if (msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN) {
               

                bKeyDown[vk] = true;
            }

            if (bKeyDown[vk] && !bPrevKeyDown[vk])
                bKeyToggle[vk] = !bKeyToggle[vk];

            if (bPrevKeyDown[vk] != bKeyDown[vk])
                bKeyClicked[vk] = bKeyDown[vk];

            if (bKeyDown[vk])
                bKeyDownRaw[vk] = true;

            bPrevKeyDown[vk] = bKeyDown[vk];
        }

        break;
    }
    default:
        break;
    }


}
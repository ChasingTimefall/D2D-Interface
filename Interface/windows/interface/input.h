#pragma once

#include "../instance.h"
#include "../../tools/vector.h"

class TInputSystem {
public:

	TInputSystem(TWinInstance* _OwningInstance) {
		OwningInstance = _OwningInstance;
	}

	bool IsPointInsideRegion(TVector2D& vecPoint,TVector2D& vecMin, TVector2D& vecMax);
	bool IsKeyToggled(int VirtualKey);
	bool IsKeyDown(int VirtualKey);
	bool IsKeyDownRaw(int VirtualKey);
	bool IsKeyClicked(int VirtualKey);
	void OnWinProc(TWinInstance* WinInstance , HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void InputStart();
	void InputFinished();
	bool IsMouseMoveInputReceived();
	bool IsMouseMoveInputReceivedDesktop();
	bool IsCursorInsideWindow();
	bool IsCursorInsideRegionRelative(const TVector2D& vecRegionRelativePosition, const TVector2D& vecRegionSize, bool bIgnoreY = false, bool bIgnoreX = false);
	std::string* GetRecentKeyInput();
public:
	TVector2D vecMousePosition;
	TVector2D vecMousePositionDelta;
public:
	TVector2D vecDesktopMousePosition;
	TVector2D vecDesktopMousePositionDelta;
private:
	std::string RecentKeyInput;
	bool bKeyDown[256];
	bool bKeyDownRaw[256];
	bool bKeyClicked[256];
	bool bPrevKeyDown[256];
	bool bKeyToggle[256];
	bool bCursorInsideWindow = false;
	bool bMouseUpdateReceived = false;
	bool bDesktopMouseUpdateReceived = false;
	TWinInstance* OwningInstance = nullptr;
	
};
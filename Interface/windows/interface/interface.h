#pragma once

#include "../instance.h"
#include "../../tools/vector.h"

struct TArea {
	TVector2D vecMin;
	TVector2D vecMax;
};

class TInputSystem;
class TInterfaceInstance {
public:
	void Create(TWinInstance* Instance, const TVector2D& _vecWindowSize);
	void Resize(const TVector2D& _vecWindowSize);
	void OnDestruction();
public:
	void PreRenderCallback(TWinInstance* Instance);
	void PostRenderCallback(TWinInstance* Instance);
	void OnWinProc(TWinInstance* Instance,HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	void HandleWindow(TWinInstance* Instance);
	bool IsInsideLockedRegion(TVector2D& vecPosition, TVector2D& vecSize);
	void LockArea(TVector2D& vecPosition,  TVector2D& vecSize);
	TInputSystem* GetInputSystem();
private:
	TArray<TArea, 1000> arrAreaLocked;
	TInputSystem* InputSystem = nullptr;
	TVector2D vecWindowSize;
};
#include "interface.h"
#include "input.h"
#include "../directx/directx.h"
#include "widgets.h"

void TInterfaceInstance::Create(TWinInstance* Instance , const TVector2D& _vecWindowSize)
{
	Resize(_vecWindowSize);
	InputSystem = new TInputSystem(Instance);
}

void TInterfaceInstance::Resize(const TVector2D& _vecWindowSize) {
	vecWindowSize = _vecWindowSize;
}

TInputSystem* TInterfaceInstance::GetInputSystem() {
	return InputSystem;
}

void TInterfaceInstance::LockArea(TVector2D& vecPosition, TVector2D& vecSize) {

	arrAreaLocked.AddBack(TArea{ vecPosition ,vecPosition + vecSize });
}

bool TInterfaceInstance::IsInsideLockedRegion(TVector2D& vecPosition, TVector2D& vecSize) {

	if (arrAreaLocked.IsEmpty())
		return false;

	TVector2D vecMax = vecPosition + vecSize;

	for (int iCurrent = 0; iCurrent < arrAreaLocked.ArraySize(); iCurrent++)
	{
		auto Object = arrAreaLocked[iCurrent];

		if (InputSystem->IsPointInsideRegion(vecPosition, Object->vecMin, Object->vecMax) || InputSystem->IsPointInsideRegion(vecPosition, Object->vecMin, Object->vecMax)
				||InputSystem->IsPointInsideRegion(Object->vecMin, vecPosition, vecMax)
				|| InputSystem->IsPointInsideRegion(Object->vecMax, vecPosition, vecMax))
			return true;

	}

	return false;
}

void TInterfaceInstance::HandleWindow(TWinInstance* Instance) 
{
	static bool bStartMoving = false;

	if (bStartMoving && !InputSystem->IsKeyDown(VK_LBUTTON))
		bStartMoving = false;

	Instance->DirectXInstance->BackgroundList->DrawRectangleFilled(TVector2D(0, 0), TVector2D(Instance->InstanceInformation->x2, Instance->InstanceInformation->y2), 24, 24, 24, 255);

	if (InputSystem->vecMousePosition.y < 30 && InputSystem->IsCursorInsideWindow())
	{
		if (InputSystem->IsKeyClicked(VK_LBUTTON))
			bStartMoving = true;

		if (InputSystem->IsMouseMoveInputReceivedDesktop())
		{
			if (bStartMoving)
			{
				if (InputSystem->vecDesktopMousePositionDelta.x || InputSystem->vecDesktopMousePositionDelta.y) {

					TVector2D vecNewPosition = TVector2D(Instance->InstanceInformation->x1 + InputSystem->vecDesktopMousePositionDelta.x,
						Instance->InstanceInformation->y1 + InputSystem->vecDesktopMousePositionDelta.y);

					if (vecNewPosition.x >= 0 && vecNewPosition.y >= 0) {
						if (SetWindowPos(Instance->hMainWindow, NULL, vecNewPosition.x, vecNewPosition.y, Instance->InstanceInformation->x2, Instance->InstanceInformation->y2, 0)) {
							Instance->InstanceInformation->x1 = vecNewPosition.x;
							Instance->InstanceInformation->y1 = vecNewPosition.y;
						}
					}
				}
			}
		}
	}
	else
		bStartMoving = false;
}

void TInterfaceInstance::PreRenderCallback(TWinInstance* Instance) {
	
	InputSystem->InputStart();
	HandleWindow(Instance);
}

void TInterfaceInstance::PostRenderCallback(TWinInstance* Instance) 
{

	Instance->DirectXInstance->BackgroundList->Render();
	Instance->DirectXInstance->ForegroundList->Render();

	arrAreaLocked.Clear();
	InputSystem->InputFinished();
}

void TInterfaceInstance::OnWinProc(TWinInstance* Instance,HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (InputSystem)
		InputSystem->OnWinProc(Instance,hWnd, msg, wParam, lParam);
}

void TInterfaceInstance::OnDestruction()
{
	if (InputSystem)
		delete InputSystem;

}
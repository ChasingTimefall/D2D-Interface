#include "../widgets.h"

CCheckboxWgt::CCheckboxWgt(const std::string& _szIdentifier, bool* _bCheckboxState, const TVector2D& vecRelativePosition, const TVector2D& vecSize)
{
	vecObjectPosition = vecRelativePosition;
	vecObjectSize = vecSize;
	WgtIndex = WGT_CHECKBOX;
	szIdentifier = _szIdentifier;
	bCheckboxState = _bCheckboxState;
}

void CCheckboxWgt::OnPostRenderCallback(TWinInstance* Instance, CWgtFrame* OwningFrame)
{
	TVector2D vecObjectPositionResolved = vecObjectPosition;

	if (OwningFrame)
		vecObjectPositionResolved = OwningFrame->vecCurrentPosition;

	if (!Instance->InterfaceInstance->IsInsideLockedRegion(vecObjectPositionResolved, vecObjectSize))
	{
		if (Instance->InterfaceInstance->GetInputSystem()->IsKeyClicked(VK_LBUTTON) && Instance->InterfaceInstance->GetInputSystem()->IsCursorInsideRegionRelative(vecObjectPositionResolved, vecObjectSize))
			*bCheckboxState = !*bCheckboxState;
	}


	Instance->DirectXInstance->BackgroundList->DrawRectangleFilled(vecObjectPositionResolved, vecObjectSize, 34, 34, 34, 255);
	Instance->DirectXInstance->BackgroundList->DrawRectangle(vecObjectPositionResolved, vecObjectSize, 15, 15, 15, 155, 1.f);

	if (*bCheckboxState)
		Instance->DirectXInstance->BackgroundList->DrawRectangleFilled(vecObjectPositionResolved + TVector2D(2, 2), vecObjectSize - TVector2D(4, 4), 144, 144, 24, 255);

	Instance->DirectXInstance->BackgroundList->RenderText(Instance->DirectXInstance->GetFont(FONTINDEX_ELEMENTTITLE), szIdentifier, vecObjectPositionResolved + vecObjectSize + TVector2D(5, -(vecObjectSize.y - 1.f)), 255, 255, 255, 255);

	if (OwningFrame)
		OwningFrame->vecCurrentPosition.y += vecObjectSize.y + 8.f;

}



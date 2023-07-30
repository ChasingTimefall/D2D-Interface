#include "../widgets.h"

CButtonWgt::CButtonWgt(const std::string& _szIdentifier, const TVector2D& vecRelativePosition, const TVector2D& vecSize)
{
	vecObjectPosition = vecRelativePosition;
	vecObjectSize = vecSize;
	WgtIndex = WGT_BUTTON;
	szIdentifier = _szIdentifier;
}

void CButtonWgt::OnPostRenderCallback(TWinInstance* Instance, CWgtFrame* OwningFrame)
{
	TVector2D vecObjectPositionResolved = vecObjectPosition;

	if (OwningFrame)
		vecObjectPositionResolved = OwningFrame->vecCurrentPosition;

	vecObjectPositionResolved.x += 20;

	bButtonClicked = false;

	if (!Instance->InterfaceInstance->IsInsideLockedRegion(vecObjectPositionResolved, vecObjectSize)) {
		if (Instance->InterfaceInstance->GetInputSystem()->IsCursorInsideRegionRelative(vecObjectPositionResolved, vecObjectSize))
		{
			if (Instance->InterfaceInstance->GetInputSystem()->IsKeyDown(VK_LBUTTON))
			{
				bKeyHeld = true;
			}
			else
			{
				if (bKeyHeld)
				{
					bButtonClicked = true;
					bKeyHeld = false;
				}
			}
		}
	}

	if (Instance->InterfaceInstance->GetInputSystem()->IsCursorInsideRegionRelative(vecObjectPositionResolved, vecObjectSize))
	{
		if (bKeyHeld || bButtonClicked) {
			Instance->DirectXInstance->BackgroundList->DrawRectangleFilled(vecObjectPositionResolved, vecObjectSize, 38, 38, 38, 255);
			Instance->DirectXInstance->BackgroundList->DrawRectangle(vecObjectPositionResolved, vecObjectSize, 15, 15, 15, 175, 1.f);
		}
		else
		{
			Instance->DirectXInstance->BackgroundList->DrawRectangleFilled(vecObjectPositionResolved, vecObjectSize, 44, 44, 44, 255);
			Instance->DirectXInstance->BackgroundList->DrawRectangle(vecObjectPositionResolved, vecObjectSize, 15, 15, 15, 175, 1.f);
		}

	}
	else
	{
		Instance->DirectXInstance->BackgroundList->DrawRectangleFilled(vecObjectPositionResolved, vecObjectSize, 34, 34, 34, 255);
		Instance->DirectXInstance->BackgroundList->DrawRectangle(vecObjectPositionResolved, vecObjectSize, 15, 15, 15, 175, 1.f);
	}

	TVector2D vecTextSize = Instance->DirectXInstance->GetTextSize(Instance->DirectXInstance->GetFont(FONTINDEX_ELEMENTTITLE), szIdentifier);

	Instance->DirectXInstance->BackgroundList->RenderText(Instance->DirectXInstance->GetFont(FONTINDEX_ELEMENTTITLE), szIdentifier, vecObjectPositionResolved + ((vecObjectSize - vecTextSize) / 2.f) , 255, 255, 255, 178);

	if (OwningFrame)
		OwningFrame->vecCurrentPosition.y += vecObjectSize.y + 8.f;

}

bool CButtonWgt::IsClicked() {
	return bButtonClicked;
}
#include "../widgets.h"

CSingleSelectWgt::CSingleSelectWgt(const std::string& _szIdentifier, const std::vector<std::string>& arrElements, int* _iValue, const TVector2D& vecRelativePosition, const TVector2D& vecSize)
{   
	vecObjectPosition = vecRelativePosition;
	vecObjectSize = vecSize;
	WgtIndex = WGT_SINGLESELECT;
	szIdentifier = _szIdentifier;
	vecElements= arrElements;
	iValue = _iValue;
}

void CSingleSelectWgt::OnPostRenderCallback(TWinInstance* Instance, CWgtFrame* OwningFrame)
{
	TVector2D vecObjectPositionRelative = vecObjectPosition;

	if (OwningFrame)
		vecObjectPositionRelative = OwningFrame->vecCurrentPosition;

	if (!szIdentifier.empty()) {
		vecObjectPositionRelative.y += Instance->DirectXInstance->GetTextSize(Instance->DirectXInstance->GetFont(FONTINDEX_ELEMENTTITLE), szIdentifier).y + 4;
		Instance->DirectXInstance->BackgroundList->RenderText(Instance->DirectXInstance->GetFont(FONTINDEX_ELEMENTTITLE), szIdentifier, (OwningFrame ? OwningFrame->vecCurrentPosition : vecObjectPosition) + TVector2D(2,0), 255, 255, 255, 255);
	}

	if (OwningFrame)
		OwningFrame->vecCurrentPosition = vecObjectPositionRelative;

	TVector2D vecBoxPosition = vecObjectPositionRelative + TVector2D(0, vecObjectSize.y + 2);
	TVector2D vecBoxSize = TVector2D(vecObjectSize.x, 2.f);

	constexpr float ElementPaddnig = 4.f;

	TVector2D vecAlignment = Instance->DirectXInstance->GetTextSize(Instance->DirectXInstance->GetFont(), vecElements.front());
	
	vecBoxSize.y += (vecAlignment.y + 4.f) * vecElements.size() - 1;
	
	if (Instance->InterfaceInstance->GetInputSystem()->IsKeyClicked(VK_LBUTTON)) {

		if (Instance->InterfaceInstance->GetInputSystem()->IsCursorInsideRegionRelative(vecObjectPositionRelative, vecObjectSize))
			bActive = !bActive;
		else
			bActive = bActive && Instance->InterfaceInstance->GetInputSystem()->IsCursorInsideRegionRelative(vecBoxPosition, vecBoxSize);

		if (bActive && Instance->InterfaceInstance->IsInsideLockedRegion(vecBoxPosition, vecBoxSize)) 
			bActive = false;
		
		if (bActive) {

			TVector2D vecElementPosition = TVector2D(vecBoxPosition.x + 2, vecBoxPosition.y + ElementPaddnig);

			for (int iCurrent = 0; iCurrent < vecElements.size(); iCurrent++)
			{
				TVector2D vecAlignment = Instance->DirectXInstance->GetTextSize(Instance->DirectXInstance->GetFont(), vecElements.at(iCurrent));

				if (Instance->InterfaceInstance->GetInputSystem()->IsCursorInsideRegionRelative(vecElementPosition, vecAlignment))
				{
					*iValue = iCurrent;
					break;
				}

				vecElementPosition.y += vecAlignment.y + ElementPaddnig;
			}
		}
	}


	Instance->DirectXInstance->BackgroundList->DrawRectangleFilled(vecObjectPositionRelative, vecObjectSize, 34, 34, 34, 255);
	Instance->DirectXInstance->BackgroundList->DrawRectangle(vecObjectPositionRelative, vecObjectSize, 15, 15, 15, 155, 1.f);

	if (bActive) {

		Instance->InterfaceInstance->LockArea(vecBoxPosition, vecBoxSize);

		Instance->DirectXInstance->ForegroundList->DrawRectangleFilled(vecBoxPosition, vecBoxSize, 34, 34, 34, 255);

		TVector2D vecElementPosition = TVector2D(vecBoxPosition.x + 2, vecBoxPosition.y + ElementPaddnig);

		for (int iCurrent = 0; iCurrent < vecElements.size(); iCurrent++)
		{
			if (iCurrent == *iValue)
				Instance->DirectXInstance->ForegroundList->RenderText(Instance->DirectXInstance->GetFont(), vecElements.at(iCurrent), vecElementPosition, 144, 144, 24, 178);
			else
				Instance->DirectXInstance->ForegroundList->RenderText(Instance->DirectXInstance->GetFont(), vecElements.at(iCurrent), vecElementPosition, 255, 255, 255, 178);

			vecElementPosition.y += vecAlignment.y + ElementPaddnig;
		}

	}

	Instance->DirectXInstance->BackgroundList->RenderText(Instance->DirectXInstance->GetFont(), vecElements.at(*iValue), vecObjectPositionRelative + TVector2D(4,4), 255, 255, 255, 178);\
	
	if (OwningFrame)
		OwningFrame->vecCurrentPosition.y += (vecObjectSize.y + 8.f);
}

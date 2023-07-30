#include "../widgets.h"
#include <algorithm>
#include "../../../tools/xorstr.h"

CSliderWgt::CSliderWgt(const std::string& _szIdentifier, void* _Input, void* _iMinValue, void* _iMaxValue, ESliderDataType SliderDataType, const TVector2D& vecRelativePosition, const TVector2D& vecSize)
{
	vecObjectPosition = vecRelativePosition;
	vecObjectSize = vecSize;
	WgtIndex = WGT_SLIDER;
	szIdentifier = _szIdentifier;
	DataType = SliderDataType;
	Input = _Input;
	MinValue = _iMinValue;
	MaxValue = _iMaxValue;
}

void CSliderWgt::OnPostRenderCallback(TWinInstance* Instance, CWgtFrame* OwningFrame)
{
	TVector2D vecObjectPositionRelative = vecObjectPosition;

	if (OwningFrame)
		vecObjectPositionRelative = OwningFrame->vecCurrentPosition;

	if (!szIdentifier.empty()) {
		vecObjectPositionRelative.y += Instance->DirectXInstance->GetTextSize(Instance->DirectXInstance->GetFont(FONTINDEX_ELEMENTTITLE), szIdentifier).y + 4;
		Instance->DirectXInstance->BackgroundList->RenderText(Instance->DirectXInstance->GetFont(FONTINDEX_ELEMENTTITLE), szIdentifier, (OwningFrame ? OwningFrame->vecCurrentPosition : vecObjectPosition) + TVector2D(2, 0), 255, 255, 255, 255);
	}

	Instance->DirectXInstance->BackgroundList->DrawRectangleFilled(vecObjectPositionRelative, vecObjectSize, 34, 34, 34, 255);
	Instance->DirectXInstance->BackgroundList->DrawRectangle(vecObjectPositionRelative, vecObjectSize, 15, 15, 15, 155, 1.f);

	float flModifer = std::clamp((Instance->InterfaceInstance->GetInputSystem()->vecMousePosition.x - vecObjectPositionRelative.x) / vecObjectSize.x, 0.0f,1.f);

	if (Instance->InterfaceInstance->GetInputSystem()->IsKeyDown(VK_LBUTTON) && Instance->InterfaceInstance->GetInputSystem()->IsCursorInsideRegionRelative(vecObjectPositionRelative, vecObjectSize))
		bActive = true;

	if (!Instance->InterfaceInstance->GetInputSystem()->IsKeyDown(VK_LBUTTON))
		bActive = false;

	if (bActive && Instance->InterfaceInstance->IsInsideLockedRegion(vecObjectPositionRelative, vecObjectSize)) 
		bActive = false;

	float flDisplayFraction = 0.01f;

	if (bActive && Instance->InterfaceInstance->GetInputSystem()->IsKeyDown(VK_LBUTTON))
	{
		if (DataType == SLIDERDATA_INT) {

			int iTotalValue = ((*(int*)MinValue) < 0 ? ((*(int*)MinValue) * -1) : (*(int*)MinValue)) + (*(int*)MaxValue);

			*(int*)Input = (int)(flModifer * (float)iTotalValue);

			if ((*(int*)MinValue) < 0 && *(int*)Input <= ((*(int*)MinValue) * -1))
				*(int*)Input = -(((*(int*)MinValue) * -1) - *(int*)Input);

		}
		else if (DataType == SLIDERDATA_FLOAT) {

			float flTotalValue = ((*(float*)MinValue) < 0.f ? ((*(float*)MinValue) * -1.f) : (*(float*)MinValue)) + (*(float*)MaxValue);

			*(float*)Input = (float)(flModifer * flTotalValue);

			if ((*(float*)MinValue) < 0.f && *(float*)Input <= ((*(float*)MinValue) * -1.f))
				*(float*)Input = -(((*(float*)MinValue) * -1.f) - *(float*)Input);

		}

	}

	TVector2D vecMax = vecObjectSize - TVector2D(2, 2);

	std::string szValueText;

	szValueText.append(1, '0');

	if (DataType == SLIDERDATA_INT) {
		flDisplayFraction = ((float)((*(int*)Input) <= 0 ? ((((*(int*)MinValue) * -1) - (*(int*)Input) * -1)) : (*(int*)Input)) / (float)(((*(int*)MinValue) < 0 ? ((*(int*)MinValue) * -1) : (*(int*)MinValue)) + (*(int*)MaxValue)));
		szValueText = std::to_string(*(int*)Input);
	}
	else if (DataType == SLIDERDATA_FLOAT) {
		flDisplayFraction = (((*(float*)Input) <= 0.f ? ((((*(float*)MinValue) * -1.f) - (*(float*)Input) * -1.f)) : (*(float*)Input)) / (((*(float*)MinValue) < 0.f ? ((*(float*)MinValue) * -1.f) : (*(float*)MinValue)) + (*(float*)MaxValue)));
		szValueText = std::to_string(*(float*)Input);
	}

	vecMax.x *= flDisplayFraction;

	Instance->DirectXInstance->BackgroundList->DrawRectangleFilled(vecObjectPositionRelative + TVector2D(1, 1), vecMax, 144, 144, 24, 255);

	TVector2D vecValueTextAlignment = Instance->DirectXInstance->GetTextSize(Instance->DirectXInstance->GetFont(), szValueText);
	Instance->DirectXInstance->BackgroundList->RenderText(Instance->DirectXInstance->GetFont(), szValueText, (OwningFrame ? OwningFrame->vecCurrentPosition : vecObjectPosition) + TVector2D(vecObjectSize.x - (vecValueTextAlignment.x + 2), 0), 255, 255, 255, 255);
	
	if (OwningFrame) {
		OwningFrame->vecCurrentPosition = vecObjectPositionRelative;
		OwningFrame->vecCurrentPosition.y += (vecObjectSize.y + 8.f);
	}
	
}
#include "../widgets.h"
#include <algorithm>

CLoadingBarWgt::CLoadingBarWgt(const std::string& _szIdentifier, float* _flProgress, const TVector2D& vecRelativePosition, const TVector2D& vecSize)
{
	vecObjectPosition = vecRelativePosition;
	vecObjectSize = vecSize;
	WgtIndex = WGT_LOADINGBAR;
	szIdentifier = _szIdentifier;
	flProgress = _flProgress;
}

void CLoadingBarWgt::OnPostRenderCallback(TWinInstance* Instance, CWgtFrame* OwningFrame)
{
	TVector2D vecObjectPositionRelative = vecObjectPosition;

	if (OwningFrame)
		vecObjectPositionRelative = OwningFrame->vecCurrentPosition;

	if ((int)(*flProgress * 100) > (int)(flProgressLocal * 100) && flProgressLocal >= 0.0f && flProgressLocal < 1.0f)
	{
		if (Instance->iTickCount % 3 == 2)
			flProgressLocal += .01f;
	}
	else if ((int)(*flProgress * 100) < (int)(flProgressLocal* 100) && flProgressLocal > 0.0f)
	{
		if (Instance->iTickCount % 3 == 2) 
			flProgressLocal -= .01f;
	}

	flProgressLocal = std::clamp(flProgressLocal, 0.0f, 1.f);

	Instance->DirectXInstance->BackgroundList->DrawRectangleFilled(vecObjectPositionRelative, vecObjectSize, 34, 34, 34, 255);
	Instance->DirectXInstance->BackgroundList->DrawRectangle(vecObjectPositionRelative, vecObjectSize, 15, 15, 15, 155, 1.f);

	TVector2D vecMax = vecObjectSize - TVector2D(2, 2);

	vecMax.x *= flProgressLocal;

	Instance->DirectXInstance->BackgroundList->DrawRectangleFilled(vecObjectPositionRelative + TVector2D(1, 1), vecMax, 144, 144, 24, 255);
	
	TVector2D vecTextSize = Instance->DirectXInstance->GetTextSize(Instance->DirectXInstance->GetFont(FONTINDEX_ELEMENTTITLE), szIdentifier);

	TVector2D vecTextPosition = vecObjectPositionRelative + ((vecObjectSize - vecTextSize) / 2.f);
	vecTextPosition.y += vecObjectSize.y * 2.f;

	Instance->DirectXInstance->BackgroundList->RenderText(Instance->DirectXInstance->GetFont(FONTINDEX_ELEMENTTITLE), szIdentifier, vecTextPosition, 255, 255, 255, 178);

	if (OwningFrame)
		OwningFrame->vecCurrentPosition.y += vecObjectSize.y + 8.f;

}

float CLoadingBarWgt::GetProgress() {
	return flProgressLocal;
}

void CLoadingBarWgt::ResetProgress() {
	flProgressLocal = 0.0f;
	*flProgress = 0.0f;
}
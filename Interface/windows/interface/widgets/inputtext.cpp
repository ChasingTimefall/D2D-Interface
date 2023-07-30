#include "../widgets.h"

CInputTextWgt::CInputTextWgt(const std::string& _szIdentifier, std::string* _szInput, bool* _bIsPasscode,const TVector2D& vecRelativePosition, const TVector2D& vecSize)
{
	vecObjectPosition = vecRelativePosition;
	vecObjectSize = vecSize;
	WgtIndex = WGT_INPUTTEXT;
	szIdentifier = _szIdentifier;
	szInput = _szInput;
	bIsPasscode = _bIsPasscode;

	if (!szInput->empty())
		for (int iCurrent = 0; iCurrent < szInput->size(); iCurrent++)
			szPasscodeString.append(1, '*');

}

void CInputTextWgt::UpdateStringExternal(const std::string& Input) {
	
	if (Input.empty())
	{
		iMaxCharacterLengthNormal = 0;
		iMaxCharacterLengthPasscode = 0;
		szInput->clear();
		szPasscodeString.clear();
		return;
	}

	*szInput = Input;

	for (int iCurrent = 0; iCurrent < szInput->size(); iCurrent++)
		szPasscodeString.append(1, '*');

	bExternalUpdateReceived = true;

}

void CInputTextWgt::OnPostRenderCallback(TWinInstance* Instance, CWgtFrame* OwningFrame)
{
	TVector2D vecObjectPositionRelative = vecObjectPosition;

	if (OwningFrame)
		vecObjectPositionRelative = OwningFrame->vecCurrentPosition;

	if (!szIdentifier.empty()) {
		vecObjectPositionRelative.y += Instance->DirectXInstance->GetTextSize(Instance->DirectXInstance->GetFont(FONTINDEX_ELEMENTTITLE), szIdentifier).y + 4;
		Instance->DirectXInstance->BackgroundList->RenderText(Instance->DirectXInstance->GetFont(FONTINDEX_ELEMENTTITLE), szIdentifier, (OwningFrame ? OwningFrame->vecCurrentPosition : vecObjectPosition) + TVector2D(2, 0), 255, 255, 255, 255);
	}

	if (OwningFrame)
	   OwningFrame->vecCurrentPosition = vecObjectPositionRelative;

	Instance->DirectXInstance->BackgroundList->DrawRectangleFilled(vecObjectPositionRelative, vecObjectSize, 34, 34, 34, 255);
	Instance->DirectXInstance->BackgroundList->DrawRectangle(vecObjectPositionRelative, vecObjectSize, 15, 15, 15, 155, 1.f);

	if (Instance->InterfaceInstance->GetInputSystem()->IsKeyClicked(VK_LBUTTON))
		bActive = Instance->InterfaceInstance->GetInputSystem()->IsCursorInsideRegionRelative(vecObjectPositionRelative, vecObjectSize);
	
	if (bActive && Instance->InterfaceInstance->IsInsideLockedRegion(vecObjectPositionRelative, vecObjectSize)) 
		bActive = false;
	
	if (bIsPasscode && *bIsPasscode)
		szDisplayString = &szPasscodeString;
	else
		szDisplayString = szInput;

	if (bExternalUpdateReceived)
	{
		iMaxCharacterLengthNormal = Instance->DirectXInstance->GetMaxTextLength(vecObjectSize - TVector2D(4, 0), Instance->DirectXInstance->GetFont(), *szInput);
		iMaxCharacterLengthPasscode = Instance->DirectXInstance->GetMaxTextLength(vecObjectSize - TVector2D(4, 0), Instance->DirectXInstance->GetFont(), szPasscodeString);
		bExternalUpdateReceived = false;
	}

	if (bActive) {

		bool bUpdateReceived = false;

		if (Instance->InterfaceInstance->GetInputSystem()->IsKeyDownRaw(VK_BACK))
		{
			if (!szInput->empty()) {
				szInput->pop_back();
				szPasscodeString.pop_back();
				bUpdateReceived = true;
			}
		}
		else
		{
			if (!Instance->InterfaceInstance->GetInputSystem()->IsKeyDownRaw(VK_RETURN))
				if (!Instance->InterfaceInstance->GetInputSystem()->GetRecentKeyInput()->empty()) {
					szInput->append(*Instance->InterfaceInstance->GetInputSystem()->GetRecentKeyInput());
					szPasscodeString.append(1, '*');
					bUpdateReceived = true;
				}

		}

		if (bUpdateReceived)
		{
			iMaxCharacterLengthNormal = Instance->DirectXInstance->GetMaxTextLength(vecObjectSize - TVector2D(4, 0), Instance->DirectXInstance->GetFont(), *szInput);
			iMaxCharacterLengthPasscode = Instance->DirectXInstance->GetMaxTextLength(vecObjectSize - TVector2D(4, 0), Instance->DirectXInstance->GetFont(), szPasscodeString);
		}

		TVector2D vecAlignment;

		if (!szDisplayString->empty())
			vecAlignment = Instance->DirectXInstance->GetTextSize(Instance->DirectXInstance->GetFont(), szDisplayString->substr(0, min(szDisplayString->size(), ((bIsPasscode && *bIsPasscode) ? iMaxCharacterLengthPasscode : iMaxCharacterLengthNormal))));
		
		if (Instance->iTickCount % 100 <= 50)
			Instance->DirectXInstance->BackgroundList->DrawLine(vecObjectPositionRelative + TVector2D(4 + vecAlignment.x, 4), vecObjectPositionRelative + TVector2D(4 + vecAlignment.x, 14), 255, 255, 255, 255, 1.0f);

	}

	if (!szDisplayString->empty())
		Instance->DirectXInstance->BackgroundList->RenderText(Instance->DirectXInstance->GetFont(), szDisplayString->substr(0, min(szDisplayString->size(), ((bIsPasscode && *bIsPasscode) ? iMaxCharacterLengthPasscode : iMaxCharacterLengthNormal))), vecObjectPositionRelative + TVector2D(4, (bIsPasscode && *bIsPasscode) ? 7.f : 5.f), 255, 255, 255, 178);

	if (OwningFrame)
		OwningFrame->vecCurrentPosition.y += (vecObjectSize.y + 8.f);

}
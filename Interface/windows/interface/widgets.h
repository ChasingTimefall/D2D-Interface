#pragma once

#include "interface.h"
#include "../instance.h"
#include "../directx/directx.h"
#include "../interface/input.h"

#define MAX_FRAME_OBJECTS 500

enum EWgtIndex {
	WGT_NIL = 0,
	WGT_FRAME,
	WGT_CHECKBOX,
	WGT_INPUTTEXT,
	WGT_SLIDER,
	WGT_SINGLESELECT,
	WGT_MULTISELECT,
	WGT_BUTTON,
	WGT_LOADINGBAR,
	WGT_MAX
};

class CWgtFrame;

class CWgtHeader {
public:
	void SetRelativePosition(const TVector2D& vecRelativePosition);
	void SetSize(const TVector2D& vecSize);
	void SetIdentifier(std::string _szIdentifier);
public:
	TVector2D vecObjectPosition;
	TVector2D vecObjectSize;
	EWgtIndex WgtIndex = WGT_CHECKBOX;
	std::string szIdentifier;
};

class CCheckboxWgt : public CWgtHeader {
public:
	CCheckboxWgt(const std::string& _szIdentifier, bool* _bCheckboxState, const TVector2D& vecRelativePosition = TVector2D(0, 0), const TVector2D& vecSize = TVector2D(13, 13));
	void OnPostRenderCallback(TWinInstance* Instance, CWgtFrame* OwningFrame = nullptr);
private:
	bool* bCheckboxState = nullptr;
};

class CInputTextWgt : public CWgtHeader {
public:
	CInputTextWgt(const std::string& _szIdentifier, std::string* _szInput, bool* bIsPasscode = nullptr, const TVector2D& vecRelativePosition = TVector2D(0, 0), const TVector2D& vecSize = TVector2D(120, 20));
	void OnPostRenderCallback(TWinInstance* Instance, CWgtFrame* OwningFrame = nullptr);
	void UpdateStringExternal(const std::string& Input);
private:
	std::string* szInput = nullptr;
	std::string* szDisplayString = nullptr;
	std::string szPasscodeString;
	bool bActive = false;
	bool* bIsPasscode = nullptr;
	int iMaxCharacterLengthNormal = 0;
	int iMaxCharacterLengthPasscode = 0;
	bool bExternalUpdateReceived = false;
	int iLastStringSize = 0;
};

enum ESliderDataType {
	SLIDERDATA_INT = 0,
	SLIDERDATA_FLOAT,
	SLIDERDATA_MAX
};

class CSliderWgt : public CWgtHeader {
public:
	CSliderWgt(const std::string& _szIdentifier, void* _Input, void* iMinValue,void* iMaxValue, ESliderDataType SliderDataType,  const TVector2D& vecRelativePosition = TVector2D(0, 0), const TVector2D& vecSize = TVector2D(120, 7));
	void OnPostRenderCallback(TWinInstance* Instance, CWgtFrame* OwningFrame = nullptr);
private:
	void* Input = nullptr;
	void* MaxValue = nullptr;
	void* MinValue = nullptr;
	ESliderDataType DataType;
	bool bActive = false;
};


class CSingleSelectWgt : public CWgtHeader {
public:
	CSingleSelectWgt(const std::string& _szIdentifier,const std::vector<std::string>& arrElements, int* _iValue, const TVector2D& vecRelativePosition = TVector2D(0, 0), const TVector2D& vecSize = TVector2D(120, 20));
	void OnPostRenderCallback(TWinInstance* Instance, CWgtFrame* OwningFrame = nullptr);
private:
	int* iValue = nullptr;
	std::vector<std::string> vecElements;
	bool bActive = false;
};

class CMultiSelectWgt : public CWgtHeader {
public:
	CMultiSelectWgt(const std::string& _szIdentifier, const std::vector<std::string>& vecElements, std::vector<bool>* arrElements, const TVector2D& vecRelativePosition = TVector2D(0, 0), const TVector2D& vecSize = TVector2D(120, 20));
	void OnPostRenderCallback(TWinInstance* Instance, CWgtFrame* OwningFrame = nullptr);
private:
	std::vector<bool>* arrElements = nullptr;
	std::vector<std::string> vecElements;
	bool bActive = false;
};

class CButtonWgt : public CWgtHeader {
public:
	CButtonWgt(const std::string& _szIdentifier, const TVector2D& vecRelativePosition = TVector2D(0, 0), const TVector2D& vecSize = TVector2D(80, 20));
	void OnPostRenderCallback(TWinInstance* Instance, CWgtFrame* OwningFrame = nullptr);
	bool IsClicked();
private:
	bool bKeyHeld = false;
	bool bButtonClicked = false;
};

class CLoadingBarWgt : public CWgtHeader {
public:
	CLoadingBarWgt(const std::string& _szIdentifier, float* _flProgress,const TVector2D& vecRelativePosition = TVector2D(0, 0), const TVector2D& vecSize = TVector2D(120, 7));
	void OnPostRenderCallback(TWinInstance* Instance, CWgtFrame* OwningFrame = nullptr);
	void ResetProgress();
	float GetProgress();
private:
	float* flProgress = nullptr;
	float flProgressLocal = 0.0f;
};

class CWgtFrame : public CWgtHeader {
public:
	CWgtFrame() {
		vecCurrentPosition = TVector2D();
		Objects.Clear();
	}
	CWgtFrame(const std::string& _szIdentifier, const TVector2D& vecRelativePosition, const TVector2D& vecSize = TVector2D(80, 20));
	void OnPostRenderCallback(TWinInstance* Instance);
	bool AddObjectToFrame(CWgtHeader* Header);
	void ClearFrame();
public:
	TVector2D vecCurrentPosition;
private:
	TArray<CWgtHeader*, MAX_FRAME_OBJECTS> Objects;
};
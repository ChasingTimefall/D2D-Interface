#pragma once

#include "../core/core.h"
#include "../tools/xorstr.h"
#include "../windows/interface/widgets.h"

class CUserInterface {
public:
	~CUserInterface();
	void InitInterface();
public:
	std::string szUsername;
	std::string szPassword;
	bool bHidePassword = true;
	float flLoadingBarProgress = 0.0f;
	int iSelectedBuild = 0;
	CLoadingBarWgt* LoadingBar = nullptr;
	CWgtFrame* MainFrame = nullptr;
	CInputTextWgt* UsernameInput = nullptr;
	CInputTextWgt* PasswordInput = nullptr;
	CCheckboxWgt* HidePassword = nullptr;
	CButtonWgt* FrameButton = nullptr;
	CButtonWgt* FrameButtonEx = nullptr;
	CSingleSelectWgt* BuildSelect = nullptr;
};


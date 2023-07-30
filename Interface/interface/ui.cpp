#include "ui.h"
#include "../core/objects.h"
#include "../tools/sharedvars.h"
#include "../tools/util.h"


void InterfaceCallback(TWinInstance* Instance) {

	TObjects::GUserInterface->MainFrame->AddObjectToFrame(TObjects::GUserInterface->UsernameInput);
	TObjects::GUserInterface->MainFrame->AddObjectToFrame(TObjects::GUserInterface->PasswordInput);
	TObjects::GUserInterface->MainFrame->AddObjectToFrame(TObjects::GUserInterface->HidePassword);
	TObjects::GUserInterface->MainFrame->AddObjectToFrame(TObjects::GUserInterface->FrameButton);
	TObjects::GUserInterface->MainFrame->AddObjectToFrame(TObjects::GUserInterface->FrameButtonEx);

	if (TObjects::GUserInterface->FrameButtonEx->IsClicked())
	{
		exit(EXIT_SUCCESS);
	}

	TObjects::GUserInterface->MainFrame->OnPostRenderCallback(Instance); //render currently stacked items on this frame
	TObjects::GUserInterface->MainFrame->ClearFrame(); //clear frame stack for new objects
}

CUserInterface::~CUserInterface() {

	if (MainFrame)
		delete MainFrame;

}

void CUserInterface::InitInterface() {

	MainFrame = new CWgtFrame(std::string(skCrypt("Frame")), TVector2D(120, 100)); 
	UsernameInput = new CInputTextWgt(std::string(skCrypt("Username")), &szUsername);
	PasswordInput = new CInputTextWgt(std::string(skCrypt("Password")), &szPassword,&bHidePassword);
	FrameButton = new CButtonWgt(std::string(skCrypt("Login")));
	FrameButtonEx = new CButtonWgt(std::string(skCrypt("Exit")));
	HidePassword = new CCheckboxWgt(std::string(skCrypt("Hide password")),&bHidePassword);
	LoadingBar = new CLoadingBarWgt(std::string(skCrypt("Checking...")), &flLoadingBarProgress);

	TObjects::GInstanceManager->CreateTransparentInstance(InterfaceCallback, std::wstring(skCrypt(L"Desktop Callback")), 350, 350, true);
}
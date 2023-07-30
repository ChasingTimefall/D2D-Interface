#include "core/core.h"
#include "core/objects.h"
#include "windows/instance.h"
#include "windows/directx/directx.h"
#include "tools/xorstr.h"
#include "windows/interface/widgets.h"
#include "interface/ui.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

    if (!TCore::Setup())
        return 0;

    TObjects::GUserInterface->InitInterface();

    while (true)
        Sleep(INT_MAX);

    return 0;
}


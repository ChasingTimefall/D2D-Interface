#include "core.h"
#include "objects.h"
#include "../tools/xorstr.h"
#include "wapi.h"

typedef DPI_AWARENESS_CONTEXT(WINAPI* PFN_SetThreadDpiAwarenessContext)(DPI_AWARENESS_CONTEXT);
typedef HRESULT(WINAPI* PFN_SetProcessDpiAwareness)(int);

bool TCore::Setup() {

	if (!TObjects::InitializeObjects())
		return false;

	if (!TImportTable::TModules::Initialize())
		return false;

	if (!TImportTable::TCurrentExecutable::SetupLibrary())
		return false;

	TIMECAPS TimeCaps;
	timeGetDevCaps(&TimeCaps, sizeof TIMECAPS);
	timeBeginPeriod(TimeCaps.wPeriodMin);

	HINSTANCE user32_dll = ::LoadLibraryA(skCrypt("user32.dll"));
	HINSTANCE shcore_dll = ::LoadLibraryA(skCrypt("shcore.dll"));
	
	if (user32_dll) {

		if (PFN_SetThreadDpiAwarenessContext SetThreadDpiAwarenessContextFn = (PFN_SetThreadDpiAwarenessContext)::GetProcAddress(user32_dll, skCrypt("SetThreadDpiAwarenessContext")))
			SetThreadDpiAwarenessContextFn(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
	}

	SetProcessDPIAware();

	if (shcore_dll != 0) {
		if (PFN_SetProcessDpiAwareness SetProcessDpiAwarenessFn = (PFN_SetProcessDpiAwareness)::GetProcAddress(shcore_dll, skCrypt("SetProcessDpiAwareness")))
			SetProcessDpiAwarenessFn(2);
	}

	return true;
}
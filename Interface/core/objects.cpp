#include "objects.h"
#include "../interface/ui.h"

// Can be switched to PAGE_GUARD Allocations to ensure safety and lateron executed through Exception Handling

bool TObjects::InitializeObjects() {

	GInstanceManager = new TInstanceManager;
	
	if (!GInstanceManager)
		return false;

	GUserInterface = new CUserInterface;

	if (!GUserInterface)
		return false;

	return true;
}
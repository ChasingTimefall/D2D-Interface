#pragma once

#include "core.h"
#include "../windows/instance.h"
#include "../interface/ui.h"

namespace TObjects {

	inline TInstanceManager* GInstanceManager = nullptr;
	inline CUserInterface* GUserInterface = nullptr;
	bool InitializeObjects();
}
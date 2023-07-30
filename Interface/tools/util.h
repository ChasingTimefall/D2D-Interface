#pragma once
#include "../core/core.h"

namespace TUtilities {

	std::wstring MultiByteToWide(const std::string& szString);
	std::string WideToMultiByte(const std::wstring& szString);
	HANDLE CreateThread(PVOID Routine,PVOID Argument = nullptr,PDWORD ThreadID = nullptr);
	bool RegSetStringValue(HKEY hRegistryKey, const std::wstring& valueName, const std::wstring& data);
	std::string RegGetStringValue(HKEY hRegistryKey, const std::string& valueName);
}

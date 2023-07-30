#include "util.h"

HANDLE TUtilities::CreateThread(PVOID Routine, PVOID Argument, PDWORD ThreadID ) {
	return ::CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)Routine,Argument,NULL,ThreadID);
}

bool TUtilities::RegSetStringValue(HKEY hRegistryKey, const std::wstring& valueName, const std::wstring& data)
{
	return ((RegSetValueExW)(hRegistryKey,
		valueName.c_str(),
		0,
		REG_SZ,
		(LPBYTE)(data.c_str()),
		(data.size() + 1) * sizeof(wchar_t)) == ERROR_SUCCESS);
}

std::string TUtilities::RegGetStringValue(HKEY hRegistryKey, const std::string& valueName) {
	
	DWORD dwBytes = 128;
	char Buffer[128];

	if (RegQueryValueExA(hRegistryKey, valueName.c_str(), nullptr, nullptr, (LPBYTE)&Buffer, &dwBytes) != ERROR_SUCCESS)
		return std::string();

	return std::string(Buffer);
}

std::string TUtilities::WideToMultiByte(const std::wstring& szString)
{
	std::string ret;
	int str_len;

	if (szString.empty())
		return {};

	str_len = WideCharToMultiByte(CP_UTF8, 0, szString.data(), (int)szString.size(), 0, 0, 0, 0);
	ret = std::string(str_len, 0);
	WideCharToMultiByte(CP_UTF8, 0, szString.data(), (int)szString.size(), &ret[0], str_len, 0, 0);

	return ret;
}

std::wstring TUtilities::MultiByteToWide(const std::string& szString)
{
	std::wstring ret;
	int str_len;

	if (szString.empty())
		return {};

	str_len = MultiByteToWideChar(CP_UTF8, 0, szString.data(), (int)szString.size(), nullptr, 0);
	ret = std::wstring(str_len, 0);
	MultiByteToWideChar(CP_UTF8, 0, szString.data(), (int)szString.size(), &ret[0], str_len);

	return ret;
}
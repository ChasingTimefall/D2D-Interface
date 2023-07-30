#include "wapi.h"
#include "../tools/xorstr.h"
\
bool TImportTable::TModules::Initialize()
{
	Kernel32 = TCurrentExecutable::GetModuleBase(skCrypt(L"KERNEL32"));

	if (!Kernel32)
		Kernel32 = TCurrentExecutable::GetModuleBase(skCrypt(L"Kernel32"));

	if (!Kernel32) 
		return false;

	TKernel32::LoadLibrayA = (FnLoadLibraryA)TCurrentExecutable::GetExportAddress(Kernel32, skCrypt("LoadLibraryA"), 0);

	NtDll = TCurrentExecutable::GetModuleBase(skCrypt(L"ntdll.dll"));

	if (!NtDll) 
		return false;

	WinTrust = TCurrentExecutable::GetModuleBase(skCrypt(L"WinTrust.dll"));

	if (!WinTrust)
		WinTrust = TKernel32::LoadLibrayA(skCrypt("WinTrust.dll"));

	if (!WinTrust)
		return false;

	TNtDll::NtQuerySystemInformation = (FnNtQuerySystemInformation)TCurrentExecutable::GetExportAddress(NtDll, skCrypt("NtQuerySystemInformation"), 1);
	TNtDll::NtQueryInformationProcess = (FnNtQueryInformationProcess)TCurrentExecutable::GetExportAddress(NtDll, skCrypt("NtQueryInformationProcess"), 2);
	TNtDll::NtQueryVirtualMemory = (FnNtQueryVirtualMemory)TCurrentExecutable::GetExportAddress(NtDll, skCrypt("NtQueryVirtualMemory"), 3);
	TNtDll::NtQuerySection = (FnNtQuerySection)TCurrentExecutable::GetExportAddress(NtDll, skCrypt("NtQuerySection"), 4);
	TNtDll::NtQueryIoCompletion = (FnNtQueryIoCompletion)TCurrentExecutable::GetExportAddress(NtDll, skCrypt("NtQueryIoCompletion"), 5);
	TNtDll::NtQueryVolumeInformationFile = (FnNtQueryVolumeInformationFile)TCurrentExecutable::GetExportAddress(NtDll, skCrypt("NtQueryVolumeInformationFile"), 6);
	TNtDll::NtQueryDirectoryFile = (FnNtQueryDirectoryFile)TCurrentExecutable::GetExportAddress(NtDll, skCrypt("NtQueryDirectoryFile"), 7);
	TNtDll::NtQueryInformationFile = (FnNtQueryInformationFile)TCurrentExecutable::GetExportAddress(NtDll, skCrypt("NtQueryInformationFile"), 8);
	TNtDll::NtQueryBootOptions = (FnNtQueryBootOptions)TCurrentExecutable::GetExportAddress(NtDll, skCrypt("NtQueryBootOptions"), 9);
	TNtDll::NtQueryBootEntryOrder = (FnNtQueryBootEntryOrder)TCurrentExecutable::GetExportAddress(NtDll, skCrypt("NtQueryBootEntryOrder"), 10);
	TNtDll::NtQuerySecurityObject = (FnNtQuerySecurityObject)TCurrentExecutable::GetExportAddress(NtDll, skCrypt("NtQuerySecurityObject"), 11);
	TNtDll::NtQuerySystemEnvironmentValue = (FnNtQuerySystemEnvironmentValue)TCurrentExecutable::GetExportAddress(NtDll, skCrypt("NtQuerySystemEnvironmentValue"), 12);
	TNtDll::NtQueryDriverEntryOrder = (FnNtQueryDriverEntryOrder)TCurrentExecutable::GetExportAddress(NtDll, skCrypt("NtQueryDriverEntryOrder"), 13);
	TNtDll::NtQueryOpenSubKeysEx = (FnNtQueryOpenSubKeysEx)TCurrentExecutable::GetExportAddress(NtDll, skCrypt("NtQueryOpenSubKeysEx"), 14);
	TNtDll::NtQueryKey = (FnNtQueryKey)TCurrentExecutable::GetExportAddress(NtDll, skCrypt("NtQueryKey"), 15);
	TNtDll::NtQueryOpenSubKeys = (FnNtQueryOpenSubKeys)TCurrentExecutable::GetExportAddress(NtDll, skCrypt("NtQueryOpenSubKeys"), 16);
	TNtDll::NtQueryValueKey = (FnNtQueryValueKey)TCurrentExecutable::GetExportAddress(NtDll, skCrypt("NtQueryValueKey"), 17);
	TNtDll::NtQueryPerformanceCounter = (FnNtQueryPerformanceCounter)TCurrentExecutable::GetExportAddress(NtDll, skCrypt("NtQueryPerformanceCounter"), 18);
	TNtDll::NtQueryInformationToken = (FnNtQueryInformationToken)TCurrentExecutable::GetExportAddress(NtDll, skCrypt("NtQueryInformationToken"), 19);
	TNtDll::NtQuerySystemTime = (FnNtQuerySystemTime)TCurrentExecutable::GetExportAddress(NtDll, skCrypt("NtQuerySystemTime"), 20);

	if (WinTrust)
	   TWinTrust::WinVerifyTrust = (FnWinVerifyTrust)TCurrentExecutable::GetExportAddress(WinTrust, skCrypt("WinVerifyTrust"), 21);
	
	TKernel32::GetModuleHandleA = (FnGetModuleHandleA)TCurrentExecutable::GetExportAddress(Kernel32, skCrypt("GetModuleHandleA"), 22);
	TNtDll::NtCreateThreadEx = (FnNtCreateThreadEx)TCurrentExecutable::GetExportAddress(NtDll, skCrypt("NtCreateThreadEx"), 23);

	TKernel32::CloseHandle = (FnCloseHandle)TCurrentExecutable::GetExportAddress(Kernel32, skCrypt("CloseHandle"), 24);
	TKernel32::CreateToolhelp32Snapshot = (FnCreateToolhelp32Snapshot)TCurrentExecutable::GetExportAddress(Kernel32, skCrypt("CreateToolhelp32Snapshot"), 25);
	TKernel32::Thread32First = (FnThread32First)TCurrentExecutable::GetExportAddress(Kernel32, skCrypt("Thread32First"), 26);
	TKernel32::Thread32Next = (FnThread32Next)TCurrentExecutable::GetExportAddress(Kernel32, skCrypt("Thread32Next"), 27);
	TNtDll::NtQueryInformationThread = (FnNtQueryInformationThread)TCurrentExecutable::GetExportAddress(NtDll, skCrypt("NtQueryInformationThread"), 28);
	TNtDll::NtClose = (FnNtClose)TCurrentExecutable::GetExportAddress(NtDll, skCrypt("NtClose"), 29);
	TKernel32::Sleep = (FnSleep)TCurrentExecutable::GetExportAddress(Kernel32, skCrypt("Sleep"), 30);
	TKernel32::QueueUserAPC = (FnQueueUserAPC)TCurrentExecutable::GetExportAddress(Kernel32, skCrypt("QueueUserAPC"), 31);
	TKernel32::OpenThread = (FnOpenThread)TCurrentExecutable::GetExportAddress(Kernel32, skCrypt("OpenThread"), 32);
	TKernel32::GetCurrentThreadId = (FnGetCurrentThreadId)TCurrentExecutable::GetExportAddress(Kernel32, skCrypt("GetCurrentThreadId"), 33);
	TKernel32::GetThreadId = (FnGetThreadId)TCurrentExecutable::GetExportAddress(Kernel32, skCrypt("GetThreadId"), 34);
	TKernel32::GetThreadContext = (FnGetThreadContext)TCurrentExecutable::GetExportAddress(Kernel32, skCrypt("GetThreadContext"), 35);

	return true;
}

PVOID TImportTable::TCurrentExecutable::GetExportAddress(PVOID pModuleBase, LPCSTR lpProcName, INT Check1, bool bIsMappedImage)
{
	return GetProcAddress((HMODULE)pModuleBase, lpProcName); // can be switched to custom GetExportAddress routine to counter hooks and patches
}

PVOID TImportTable::TCurrentExecutable::GetModuleBase(LPCWSTR ModuleName)
{
	PPEB pPeb = GetPeb();

	for (PLIST_ENTRY pListEntry = (PLIST_ENTRY)pPeb->Ldr->InLoadOrderModuleList.Flink;
		pListEntry != &pPeb->Ldr->InLoadOrderModuleList; pListEntry = (PLIST_ENTRY)pListEntry->Flink) {

		PLDR_DATA_TABLE_ENTRY pEntry = CONTAINING_RECORD(pListEntry, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);

		std::wstring szModuleName = pEntry->BaseDllName.Buffer;

		if (szModuleName.find(ModuleName) != std::wstring::npos)
			return pEntry->DllBase;
	}

	return NULL;
}

PPEB TImportTable::TCurrentExecutable::GetPeb()
{
#if defined(_M_X64) || defined(__amd64__)
	return reinterpret_cast<PPEB>(__readgsqword(0x60));
#elif defined(_M_IX86) || defined(__i386__)
	return reinterpret_cast<PPEB>(__readfsdword(0x30));
#else
	if (GetTeb())
		return (PPEB)GetTeb()->Peb;
	else
		return 0x0;
#endif
}

PTEB TImportTable::TCurrentExecutable::GetTeb()
{
	return reinterpret_cast<PTEB>(
#ifdef _M_X64
		__readgsqword(offsetof(NT_TIB, Self))
#elif _M_IX86
		__readfsdword(offsetof(NT_TIB, Self))
#else
		0x0
#endif
		);
}

bool TImportTable::TCurrentExecutable::SetupLibrary() {
	pExecutableBase = TImportTable::TCurrentExecutable::GetPeb()->ImageBaseAddress;
	dwProcessID = (DWORD)TImportTable::TCurrentExecutable::GetTeb()->ClientId.UniqueProcess;
	dwUniqueThreadID = (DWORD)TImportTable::TCurrentExecutable::GetTeb()->ClientId.UniqueThread;
	return true;
}
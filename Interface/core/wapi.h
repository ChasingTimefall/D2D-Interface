#pragma once

#include "core.h"
#include <string_view>

#define USERMODE_ADDRESS_MAX 0xFFFF000000000000   //Overridable 
#define KERNEMODE_ADDRESS_START USERMODE_ADDRESS_MAX

enum SYSTEM_INFORMATION_CLASS {
	SystemBasicInformation = 0x0,
	SystemProcessorInformation = 0x01,
	SystemCodeIntegrityInformation = 0x67,
	SystemCodeIntegrityPolicyInformation = 0xA4,
	SystemCodeIntegrityPoliciesFullInformation = 0xBD,
	SystemCodeIntegrityCertificateInformation = 0xB7,
	SystemCodeIntegrityUnlockInformation = 0xBE,
	SystemCodeIntegrityVerificationInformation = 0xC7,
	SystemCodeIntegrityUnlockModeInformation = 0xCD,
	SystemCodeIntegritySyntheticCacheInformation = 0xD1,
	SystemCodeIntegrityPlatformManifestInformation = 0xB3,
	SystemIsolatedUserModeInformation = 0xA5,
	MaxSystemInfoClass = 0xD6,
};

enum PROCESSINFOCLASS {
	ProcessBasicInformation = 0,
	ProcessDebugPort = 7,
	ProcessQuotaLimits = 1,
	ProcessIoCounters = 2,
	ProcessVmCounters = 3,
	ProcessTimes = 4,
	ProcessBasePriority = 5,
	ProcessRaisePriority = 6,
	ProcessExceptionPort = 8,
	ProcessAccessToken = 9,
	ProcessLdtInformation = 10,
	ProcessLdtSize = 11,
	ProcessDefaultHardErrorMode = 12,
	ProcessIoPortHandlers = 13,
	ProcessPooledUsageAndLimits = 14,
	ProcessWorkingSetWatch = 15,
	ProcessUserModeIOPL = 16,
	ProcessEnableAlignmentFaultFixup = 17,
	ProcessPriorityClass = 18,
	ProcessWx86Information = 19,
	ProcessHandleCount = 20,
	ProcessAffinityMask = 21,
	ProcessPriorityBoost = 22,
	ProcessDeviceMap = 23,
	ProcessSessionInformation = 24,
	ProcessForegroundInformation = 25,
	ProcessWow64Information = 26,
	ProcessImageFileName = 27,
	ProcessLUIDDeviceMapsEnabled = 28,
	ProcessBreakOnTermination = 29,
	ProcessDebugObjectHandle = 30,
	ProcessDebugFlags = 31,
	ProcessHandleTracing = 32,
	ProcessExecuteFlags = 34,
	ProcessTlsInformation = 35,
	ProcessCookie = 36,
	ProcessImageInformation = 37,
	ProcessCycleTime = 38,
	ProcessPagePriority = 39,
	ProcessInstrumentationCallback = 40,
	ProcessThreadStackAllocation = 41,
	ProcessWorkingSetWatchEx = 42,
	ProcessImageFileNameWin32 = 43,
	ProcessImageFileMapping = 44,
	ProcessAffinityUpdateMode = 45,
	ProcessMemoryAllocationMode = 46,
	ProcessGroupInformation = 47,
	ProcessTokenVirtualizationEnabled = 48,
	ProcessConsoleHostProcess = 49,
	ProcessWindowInformation = 50,
	MaxProcessInfoClass,
};

typedef enum _MEMORY_INFORMATION_CLASS {
	MemoryBasicInformation,
	MemoryWorkingSetList,
	MemorySectionName,
	MemoryBasicVlmInformation,
	MemoryWorkingSetExList,
} MEMORY_INFORMATION_CLASS;

enum SECTION_INFORMATION_CLASS
{
	SectionBasicInformation = 0,
	SectionImageInformation,
};

enum FS_INFORMATION_CLASS {
	FileFsVolumeInformation = 1,
	FileFsLabelInformation,
	FileFsSizeInformation,
	FileFsDeviceInformation,
	FileFsAttributeInformation,
	FileFsControlInformation,
	FileFsFullSizeInformation,
	FileFsObjectIdInformation,
	FileFsDriverPathInformation,
	FileFsVolumeFlagsInformation,
	FileFsMaximumInformation
};


enum IO_COMPLETION_INFORMATION_CLASS {
	IoCompletionBasicInformation = 0,
};

enum FILE_INFORMATION_CLASS {
	FileDirectoryInformation = 1,
	FileFullDirectoryInformation,
	FileBothDirectoryInformation,
	FileBasicInformation,
	FileStandardInformation,
	FileInternalInformation,
	FileEaInformation,
	FileAccessInformation,
	FileNameInformation,
	FileRenameInformation,
	FileLinkInformation,
	FileNamesInformation,
	FileDispositionInformation,
	FilePositionInformation,
	FileFullEaInformation,
	FileModeInformation,
	FileAlignmentInformation,
	FileAllInformation,
	FileAllocationInformation,
	FileEndOfFileInformation,
	FileAlternateNameInformation,
	FileStreamInformation,
	FilePipeInformation,
	FilePipeLocalInformation,
	FilePipeRemoteInformation,
	FileMailslotQueryInformation,
	FileMailslotSetInformation,
	FileCompressionInformation,
	FileObjectIdInformation,
	FileCompletionInformation,
	FileMoveClusterInformation,
	FileQuotaInformation,
	FileReparsePointInformation,
	FileNetworkOpenInformation,
	FileAttributeTagInformation,
	FileTrackingInformation,
	FileIdBothDirectoryInformation,
	FileIdFullDirectoryInformation,
	FileValidDataLengthInformation,
	FileShortNameInformation,
	FileIoCompletionNotificationInformation,
	FileIoStatusBlockRangeInformation,
	FileIoPriorityHintInformation,
	FileSfioReserveInformation,
	FileSfioVolumeInformation,
	FileHardLinkInformation,
	FileProcessIdsUsingFileInformation,
	FileNormalizedNameInformation,
	FileNetworkPhysicalNameInformation,
	FileIdGlobalTxDirectoryInformation,
	FileMaximumInformation
};

typedef enum _KEY_INFORMATION_CLASS {
	KeyBasicInformation,
	KeyNodeInformation,
	KeyFullInformation
} KEY_INFORMATION_CLASS;

typedef enum _KEY_VALUE_INFORMATION_CLASS {
	KeyValueBasicInformation,
	KeyValueFullInformation,
	KeyValuePartialInformation
} KEY_VALUE_INFORMATION_CLASS;

typedef enum _THREADINFOCLASS {
	ThreadBasicInformation,
	ThreadTimes,
	ThreadPriority,
	ThreadBasePriority,
	ThreadAffinityMask,
	ThreadImpersonationToken,
	ThreadDescriptorTableEntry,
	ThreadEnableAlignmentFaultFixup,
	ThreadEventPair_Reusable,
	ThreadQuerySetWin32StartAddress,
	ThreadZeroTlsCell,
	ThreadPerformanceCount,
	ThreadAmILastThread,
	ThreadIdealProcessor,
	ThreadPriorityBoost,
	ThreadSetTlsArrayAddress,
	ThreadIsIoPending,
	ThreadHideFromDebugger,
	ThreadBreakOnTermination,
	ThreadSwitchLegacyState,
	ThreadIsTerminated,
	ThreadLastSystemCall,
	ThreadIoPriority,
	ThreadCycleTime,
	ThreadPagePriority,
	ThreadActualBasePriority,
	ThreadTebInformation,
	ThreadCSwitchMon,
	ThreadCSwitchPmu,
	ThreadWow64Context,
	ThreadGroupInformation,
	ThreadUmsInformation,
	ThreadCounterProfiling,
	ThreadIdealProcessorEx,
	MaxThreadInfoClass
} THREADINFOCLASS;


typedef struct _IO_STATUS_BLOCK {
	ULONG Status;
	ULONG Information;
} IO_STATUS_BLOCK, * PIO_STATUS_BLOCK;

typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWSTR  Buffer;
} UNICODE_STRING;
typedef UNICODE_STRING* PUNICODE_STRING;

typedef struct _BOOT_OPTIONS
{
	ULONG Version;
	ULONG Length;
	ULONG Timeout;
	ULONG CurrentBootEntryId;
	ULONG NextBootEntryId;
	WCHAR HeadlessRedirection[1];
} BOOT_OPTIONS, * PBOOT_OPTIONS;

typedef struct _OBJECT_ATTRIBUTES
{
	ULONG Length;
	HANDLE RootDirectory;
	PUNICODE_STRING ObjectName;
	ULONG Attributes;
	PVOID SecurityDescriptor;
	PVOID SecurityQualityOfService;
} OBJECT_ATTRIBUTES, * POBJECT_ATTRIBUTES;

typedef struct _PEB_LDR_DATA {
	ULONG Length;
	ULONG Initialized;
	HANDLE SsHandle;
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
	PVOID EntryInProgress;
	BOOLEAN ShutdownInProgress;
	HANDLE ShutdownThreadId;
} PEB_LDR_DATA, * PPEB_LDR_DATA;

typedef struct _RTL_USER_PROCESS_PARAMETERS {
	BYTE           Reserved1[16];
	PVOID          Reserved2[10];
	UNICODE_STRING ImagePathName;
	UNICODE_STRING CommandLine;
} RTL_USER_PROCESS_PARAMETERS, * PRTL_USER_PROCESS_PARAMETERS;

typedef VOID(NTAPI* PPS_POST_PROCESS_INIT_ROUTINE) (VOID);
typedef struct _PEB {
	BYTE                          Reserved1[2];
	BYTE                          BeingDebugged;
	union
	{
		BOOLEAN BitField;
		struct
		{
			BOOLEAN ImageUsesLargePages : 1;
			BOOLEAN IsProtectedProcess : 1;
			BOOLEAN IsImageDynamicallyRelocated : 1;
			BOOLEAN SkipPatchingUser32Forwarders : 1;
			BOOLEAN IsPackagedProcess : 1;
			BOOLEAN IsAppContainer : 1;
			BOOLEAN IsProtectedProcessLight : 1;
			BOOLEAN SpareBits : 1;
		};
	};
	HANDLE Mutant;
	PVOID ImageBaseAddress;
	PPEB_LDR_DATA                 Ldr;
	PRTL_USER_PROCESS_PARAMETERS  ProcessParameters;
	PVOID                         Reserved4[3];
	PVOID                         AtlThunkSListPtr;
	PVOID                         Reserved5;
	ULONG                         Reserved6;
	PVOID                         Reserved7;
	ULONG                         Reserved8;
	ULONG                         AtlThunkSListPtr32;
	PVOID                         Reserved9[45];
	BYTE                          Reserved10[96];
	PPS_POST_PROCESS_INIT_ROUTINE PostProcessInitRoutine;
	BYTE                          Reserved11[128];
	PVOID                         Reserved12[1];
	ULONG                         SessionId;
} PEB, * PPEB;

typedef struct _CLIENT_ID
{
	HANDLE UniqueProcess;
	HANDLE UniqueThread;
} CLIENT_ID, * PCLIENT_ID;

#define GDI_BATCH_BUFFER_SIZE 0x136

typedef struct _GDI_TEB_BATCH
{
	ULONG Offset;
	HANDLE HDC;
	ULONG Buffer[GDI_BATCH_BUFFER_SIZE];
} GDI_TEB_BATCH, * PGDI_TEB_BATCH;

typedef struct _TEB
{
	NT_TIB          Tib;
	PVOID           EnvironmentPointer;
	CLIENT_ID       ClientId;
	PVOID           ActiveRpcHandle;
	PVOID           ThreadLocalStoragePointer;
	PVOID           Peb;
	ULONG           LastErrorValue;
	ULONG           CountOfOwnedCriticalSections;
	PVOID           CsrClientThread;
	PVOID           Win32ThreadInfo;
	ULONG           Win32ClientInfo[31];
	PVOID           WOW32Reserved;
	ULONG           CurrentLocale;
	ULONG           FpSoftwareStatusRegister;
	PVOID           SystemReserved1[54];
	PVOID           Spare1;
	LONG            ExceptionCode;
	PVOID     ActivationContextStackPointer;
	BYTE            SpareBytes1[36];
	PVOID           SystemReserved2[10];
	GDI_TEB_BATCH   GdiTebBatch;
	ULONG           gdiRgn;
	ULONG           gdiPen;
	ULONG           gdiBrush;
	CLIENT_ID       RealClientId;
	HANDLE          GdiCachedProcessHandle;
	ULONG           GdiClientPID;
	ULONG           GdiClientTID;
	PVOID           GdiThreadLocaleInfo;
	PVOID           UserReserved[5];
	PVOID           glDispatchTable[280];
	ULONG           glReserved1[26];
	PVOID           glReserved2;
	PVOID           glSectionInfo;
	PVOID           glSection;
	PVOID           glTable;
	PVOID           glCurrentRC;
	PVOID           glContext;
	ULONG           LastStatusValue;
	UNICODE_STRING  StaticUnicodeString;
	WCHAR           StaticUnicodeBuffer[261];
	PVOID           DeallocationStack;
	PVOID           TlsSlots[64];
	LIST_ENTRY      TlsLinks;
	PVOID           Vdm;
	PVOID           ReservedForNtRpc;
	PVOID           DbgSsReserved[2];
	ULONG           HardErrorDisabled;
	PVOID           Instrumentation[16];
	PVOID           WinSockData;
	ULONG           GdiBatchCount;
	ULONG           Spare2;
	ULONG           Spare3;
	ULONG           Spare4;
	PVOID           ReservedForOle;
	ULONG           WaitingOnLoaderLock;
	PVOID           Reserved5[3];
	PVOID* TlsExpansionSlots;
} TEB, * PTEB;

typedef struct _LDR_DATA_TABLE_ENTRY {
	LIST_ENTRY InLoadOrderLinks;
	LIST_ENTRY InMemoryOrderLinks;
	LIST_ENTRY InInitializationOrderLinks;
	PVOID DllBase;
	PVOID EntryPoint;
	union {
		unsigned long SizeOfImage;
		PVOID _dummy;
	};
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
}LDR_DATA_TABLE_ENTRY, * PLDR_DATA_TABLE_ENTRY;

typedef VOID(*TL_FN_FREE)(PVOID);
typedef struct _TL
{
	struct _TL* next;
	PVOID pobj;
	TL_FN_FREE pfnFree;
} TL, * PTL;

typedef struct _ETHREAD;
typedef _ETHREAD* PETHREAD;

typedef struct _EPROCESS;
typedef _EPROCESS* PEPROCESS;

typedef struct _KTHREAD;
typedef _KTHREAD* PKTHREAD;

typedef struct _THREADINFO;
typedef _THREADINFO* PTHREADINFO;

typedef struct _PROCESSINFO;
typedef _PROCESSINFO* PPROCESSINFO;

typedef struct tagIMC;

typedef struct _W32THREAD
{
	PETHREAD pEThread;
	LONG RefCount;
	PTL ptlW32;
	PVOID pgdiDcattr;
	PVOID pgdiBrushAttr;
	PVOID pUMPDObjs;
	PVOID pUMPDHeap;
	DWORD dwEngAcquireCount;
	PVOID pSemTable;
	PVOID pUMPDObj;
} W32THREAD, * PW32THREAD;



typedef struct _EX_PUSH_LOCK
{
	union
	{
		struct
		{
			ULONG_PTR Locked : 1;
			ULONG_PTR Waiting : 1;
			ULONG_PTR Waking : 1;
			ULONG_PTR MultipleShared : 1;
			ULONG_PTR Shared : sizeof(ULONG_PTR) * 8 - 4;
		};
		ULONG_PTR Value;
		PVOID Ptr;
	};
} EX_PUSH_LOCK, * PEX_PUSH_LOCK;

typedef struct _RTL_BALANCED_LINKS {
	struct _RTL_BALANCED_LINKS* Parent;
	struct _RTL_BALANCED_LINKS* LeftChild;
	struct _RTL_BALANCED_LINKS* RightChild;
	CHAR Balance;
	UCHAR Reserved[3];
} RTL_BALANCED_LINKS, * PRTL_BALANCED_LINKS;


typedef struct _RTL_AVL_TABLE {
	RTL_BALANCED_LINKS BalancedRoot;
	PVOID OrderedPointer;
	ULONG WhichOrderedElement;
	ULONG NumberGenericTableElements;
	ULONG DepthOfTree;
	PRTL_BALANCED_LINKS RestartKey;
	ULONG DeleteCount;
	PVOID CompareRoutine;
	PVOID AllocateRoutine;
	PVOID FreeRoutine;
	PVOID TableContext;
} RTL_AVL_TABLE, * PRTL_AVL_TABLE;


#define TIMER_TOLERABLE_DELAY_BITS      6
#define TIMER_EXPIRED_INDEX_BITS        6
#define TIMER_PROCESSOR_INDEX_BITS      5

typedef struct _DISPATCHER_HEADER {
	union {
		union {
			volatile LONG Lock;
			LONG LockNV;
		} DUMMYUNIONNAME;

		struct {                            // Events, Semaphores, Gates, etc.
			UCHAR Type;                     // All (accessible via KOBJECT_TYPE)
			UCHAR Signalling;
			UCHAR Size;
			UCHAR Reserved1;
		} DUMMYSTRUCTNAME;

		struct {                            // Timer
			UCHAR TimerType;
			union {
				UCHAR TimerControlFlags;
				struct {
					UCHAR Absolute : 1;
					UCHAR Wake : 1;
					UCHAR EncodedTolerableDelay : TIMER_TOLERABLE_DELAY_BITS;
				} DUMMYSTRUCTNAME;
			};

			UCHAR Hand;
			union {
				UCHAR TimerMiscFlags;
				struct {

#if !defined(KENCODED_TIMER_PROCESSOR)

					UCHAR Index : TIMER_EXPIRED_INDEX_BITS;

#else

					UCHAR Index : 1;
					UCHAR Processor : TIMER_PROCESSOR_INDEX_BITS;

#endif

					UCHAR Inserted : 1;
					volatile UCHAR Expired : 1;
				} DUMMYSTRUCTNAME;
			} DUMMYUNIONNAME;
		} DUMMYSTRUCTNAME2;

		struct {                            // Timer2
			UCHAR Timer2Type;
			union {
				UCHAR Timer2Flags;
				struct {
					UCHAR Timer2Inserted : 1;
					UCHAR Timer2Expiring : 1;
					UCHAR Timer2CancelPending : 1;
					UCHAR Timer2SetPending : 1;
					UCHAR Timer2Running : 1;
					UCHAR Timer2Disabled : 1;
					UCHAR Timer2ReservedFlags : 2;
				} DUMMYSTRUCTNAME;
			} DUMMYUNIONNAME;

			UCHAR Timer2ComponentId;
			UCHAR Timer2RelativeId;
		} DUMMYSTRUCTNAME3;

		struct {                            // Queue
			UCHAR QueueType;
			union {
				UCHAR QueueControlFlags;
				struct {
					UCHAR Abandoned : 1;
					UCHAR DisableIncrement : 1;
					UCHAR QueueReservedControlFlags : 6;
				} DUMMYSTRUCTNAME;
			} DUMMYUNIONNAME;

			UCHAR QueueSize;
			UCHAR QueueReserved;
		} DUMMYSTRUCTNAME4;

		struct {                            // Thread
			UCHAR ThreadType;
			UCHAR ThreadReserved;

			union {
				UCHAR ThreadControlFlags;
				struct {
					UCHAR CycleProfiling : 1;
					UCHAR CounterProfiling : 1;
					UCHAR GroupScheduling : 1;
					UCHAR AffinitySet : 1;
					UCHAR Tagged : 1;
					UCHAR EnergyProfiling : 1;
					UCHAR SchedulerAssist : 1;

#if !defined(_X86_)

					UCHAR ThreadReservedControlFlags : 1;

#else

					UCHAR Instrumented : 1;

#endif

				} DUMMYSTRUCTNAME;
			} DUMMYUNIONNAME;

			union {
				UCHAR DebugActive;

#if !defined(_X86_)

				struct {
					BOOLEAN ActiveDR7 : 1;
					BOOLEAN Instrumented : 1;
					BOOLEAN Minimal : 1;
					BOOLEAN Reserved4 : 2;
					BOOLEAN AltSyscall : 1;
					BOOLEAN Emulation : 1;
					BOOLEAN Reserved5 : 1;
				} DUMMYSTRUCTNAME;

#endif

			} DUMMYUNIONNAME2;
		} DUMMYSTRUCTNAME5;

		struct {                         // Mutant
			UCHAR MutantType;
			UCHAR MutantSize;
			BOOLEAN DpcActive;
			UCHAR MutantReserved;
		} DUMMYSTRUCTNAME6;
	} DUMMYUNIONNAME;

	LONG SignalState;                   // Object lock
	LIST_ENTRY WaitListHead;            // Object lock
} DISPATCHER_HEADER, * PDISPATCHER_HEADER;

typedef struct _KEVENT {
	DISPATCHER_HEADER Header;
} KEVENT, * PKEVENT, * RESTRICTED_POINTER PRKEVENT;

typedef struct _W32PROCESS
{
	PEPROCESS     peProcess;
	DWORD         RefCount;
	ULONG         W32PF_flags;
	PKEVENT       InputIdleEvent;
	DWORD         StartCursorHideTime;
	struct _W32PROCESS* NextStart;
	PVOID         pDCAttrList;
	PVOID         pBrushAttrList;
	DWORD         W32Pid;
	LONG          GDIHandleCount;
	LONG          UserHandleCount;
	PEX_PUSH_LOCK GDIPushLock;
	RTL_AVL_TABLE GDIEngUserMemAllocTable;
	LIST_ENTRY    GDIDcAttrFreeList;
	LIST_ENTRY    GDIBrushAttrFreeList;
} W32PROCESS, * PW32PROCESS;

typedef struct tagUSERSTARTUPINFO
{
	ULONG cb;
	DWORD dwX;
	DWORD dwY;
	DWORD dwXSize;
	DWORD dwYSize;
	DWORD dwFlags;
	WORD wShowWindow;
	USHORT cbReserved2;
} USERSTARTUPINFO, * PUSERSTARTUPINFO;



typedef struct _FAST_MUTEX {
	volatile LONG Count;
	PKTHREAD Owner;
	ULONG Contention;
	KEVENT Event;
	ULONG OldIrql;
} FAST_MUTEX, * PFAST_MUTEX;

typedef struct _W32HEAP_USER_MAPPING
{
	struct _W32HEAP_USER_MAPPING* Next;
	PVOID KernelMapping;
	PVOID UserMapping;
	ULONG_PTR Limit;
	ULONG Count;
} W32HEAP_USER_MAPPING, * PW32HEAP_USER_MAPPING;

#define CLIBS 32
typedef struct _PROCESSINFO : _W32PROCESS
{
	PTHREADINFO ptiList;
	PTHREADINFO ptiMainThread;
	struct _DESKTOP* rpdeskStartup;
	struct _CLS* pclsPrivateList;
	struct _CLS* pclsPublicList;
	PPROCESSINFO ppiNext;
	INT cThreads;
	HDESK hdeskStartup;
	DWORD dwhmodLibLoadedMask;
	HANDLE ahmodLibLoaded[CLIBS];
	struct _WINSTATION_OBJECT* prpwinsta;
	HWINSTA hwinsta;
	ACCESS_MASK amwinsta;
	DWORD dwHotkey;
	HMONITOR hMonitor;
	UINT iClipSerialNumber;
	struct _CURICON_OBJECT* pCursorCache;
	PVOID pClientBase;
	DWORD dwLpkEntryPoints;
	PVOID pW32Job;
	DWORD dwImeCompatFlags;
	LUID luidSession;
	USERSTARTUPINFO usi;
	DWORD dwLayout;
	DWORD dwRegisteredClasses;
	FAST_MUTEX PrivateFontListLock;
	LIST_ENTRY PrivateFontListHead;
	LIST_ENTRY PrivateMemFontListHead;
	UINT PrivateMemFontHandleCount;
	FAST_MUTEX DriverObjListLock;
	LIST_ENTRY DriverObjListHead;
	W32HEAP_USER_MAPPING HeapMappings;
	struct _GDI_POOL* pPoolDcAttr;
	struct _GDI_POOL* pPoolBrushAttr;
	struct _GDI_POOL* pPoolRgnAttr;

} PROCESSINFO, * PPROCESSINFO;

typedef struct _THREADINFO : _W32THREAD
{
	PTL                 ptl;
	PPROCESSINFO        ppi;
	struct _USER_MESSAGE_QUEUE* MessageQueue;
	struct tagKL* KeyboardLayout;
	struct _CLIENTTHREADINFO* pcti;
	struct _DESKTOP* rpdesk;
	struct _DESKTOPINFO* pDeskInfo;
	struct _CLIENTINFO* pClientInfo;
	FLONG               TIF_flags;
	PUNICODE_STRING     pstrAppName;
	struct _USER_SENT_MESSAGE* pusmSent;
	struct _USER_SENT_MESSAGE* pusmCurrent;
	LIST_ENTRY          SentMessagesListHead;
	LONG                timeLast;
	ULONG_PTR           idLast;
	BOOLEAN             QuitPosted;
	INT                 exitCode;
	HDESK               hdesk;
	UINT                cPaintsReady;
	UINT                cTimersReady;
	struct tagMENUSTATE* pMenuState;
	DWORD               dwExpWinVer;
	DWORD               dwCompatFlags;
	DWORD               dwCompatFlags2;
	struct _USER_MESSAGE_QUEUE* pqAttach;
	PTHREADINFO         ptiSibling;
	ULONG               fsHooks;
	struct tagHOOK* sphkCurrent;
	LPARAM              lParamHkCurrent;
	WPARAM              wParamHkCurrent;
	struct tagSBTRACK* pSBTrack;
	HANDLE              hEventQueueClient;
	PKEVENT             pEventQueueServer;
	LIST_ENTRY          PtiLink;
	INT                 iCursorLevel;
	POINT               ptLast;
	struct _WND* spwndDefaultIme;
	struct tagIMC* spDefaultImc;
	HKL                 hklPrev;

	INT                 cEnterCount;
	LIST_ENTRY          PostedMessagesListHead;
	WORD                fsChangeBitsRemoved;
	WCHAR               wchInjected;
	UINT                cWindows;
	UINT                cVisWindows;
} THREADINFO, * PTHREADINFO;

typedef struct _SYSTEM_CODEINTEGRITY_INFORMATION {
	ULONG  Length;
	ULONG  CodeIntegrityOptions;
} SYSTEM_CODEINTEGRITY_INFORMATION, * PSYSTEM_CODEINTEGRITY_INFORMATION;

typedef struct _SYSTEM_ISOLATED_USER_MODE_INFORMATION
{
	BOOLEAN SecureKernelRunning : 1;
	BOOLEAN HvciEnabled : 1;
	BOOLEAN HvciStrictMode : 1;
	BOOLEAN DebugEnabled : 1;
	BOOLEAN FirmwarePageProtection : 1;
	BOOLEAN EncryptionKeyAvailable : 1;
	BOOLEAN SpareFlags : 2;
	BOOLEAN TrustletRunning : 1;
	BOOLEAN HvciDisableAllowed : 1;
	BOOLEAN SpareFlags2 : 6;
	BOOLEAN Spare0[6];
	ULONGLONG Spare1;
} SYSTEM_ISOLATED_USER_MODE_INFORMATION, * PSYSTEM_ISOLATED_USER_MODE_INFORMATION;


typedef void(WINAPI* PIO_APC_ROUTINE) (PVOID, PIO_STATUS_BLOCK, ULONG);

using FnLoadLibraryA = HMODULE(WINAPI*)(LPCSTR);
using FnGetModuleHandleA = HMODULE(WINAPI*)(LPCSTR);

using FnNtQuerySystemInformation = NTSTATUS(NTAPI*)(SYSTEM_INFORMATION_CLASS, PVOID, ULONG, PULONG);
using FnNtQueryInformationProcess = NTSTATUS(NTAPI*)(HANDLE, PROCESSINFOCLASS, PVOID, ULONG, PULONG);
using FnNtQueryVirtualMemory = NTSTATUS(NTAPI*)(HANDLE, PVOID, MEMORY_INFORMATION_CLASS, PVOID, SIZE_T, PSIZE_T);
using FnNtQuerySection = NTSTATUS(WINAPI*)(HANDLE, SECTION_INFORMATION_CLASS, PVOID, SIZE_T, SIZE_T*);
using FnNtQueryIoCompletion = NTSTATUS(WINAPI*)(HANDLE, IO_COMPLETION_INFORMATION_CLASS, PVOID, ULONG, PULONG);
using FnNtQueryVolumeInformationFile = NTSTATUS(NTAPI*)(HANDLE, PIO_STATUS_BLOCK, PVOID, ULONG, FS_INFORMATION_CLASS);
using FnNtQueryDirectoryFile = NTSTATUS(NTAPI*)(HANDLE, HANDLE, PIO_APC_ROUTINE, PVOID, PIO_STATUS_BLOCK, PVOID, ULONG, FILE_INFORMATION_CLASS, BOOLEAN, PUNICODE_STRING, BOOLEAN);
using FnNtQueryInformationFile = NTSTATUS(WINAPI*)(HANDLE, PIO_STATUS_BLOCK, PVOID, LONG, FILE_INFORMATION_CLASS);
using FnNtQueryBootOptions = NTSTATUS(NTAPI*)(PBOOT_OPTIONS, PULONG);
using FnNtQueryBootEntryOrder = NTSTATUS(NTAPI*)(PULONG, PULONG);
using FnNtQuerySecurityObject = NTSTATUS(WINAPI*)(HANDLE, SECURITY_INFORMATION, PSECURITY_DESCRIPTOR, ULONG, PULONG);
using FnNtQuerySystemEnvironmentValue = NTSTATUS(WINAPI*)(PUNICODE_STRING, PWCHAR, ULONG, PULONG);
using FnNtQueryDriverEntryOrder = NTSTATUS(NTAPI*)(PULONG, PULONG);
using FnNtQueryOpenSubKeysEx = NTSTATUS(NTAPI*)(POBJECT_ATTRIBUTES, ULONG, PVOID, PULONG);
using FnNtQueryKey = NTSTATUS(WINAPI*)(HANDLE, KEY_INFORMATION_CLASS, PVOID, DWORD, DWORD*);
using FnNtQueryOpenSubKeys = NTSTATUS(WINAPI*)(POBJECT_ATTRIBUTES, PULONG);
using FnNtQueryValueKey = NTSTATUS(WINAPI*)(HANDLE, const UNICODE_STRING*, KEY_VALUE_INFORMATION_CLASS, PVOID, DWORD, DWORD*);
using FnNtQueryPerformanceCounter = NTSTATUS(WINAPI*)(PLARGE_INTEGER, PLARGE_INTEGER);
using FnNtQueryInformationToken = NTSTATUS(WINAPI*)(HANDLE, TOKEN_INFORMATION_CLASS, PVOID, ULONG, PULONG);
using FnNtQuerySystemTime = NTSTATUS(WINAPI*)(PLARGE_INTEGER);

using FnNtQueryInformationThread = NTSTATUS(NTAPI*)(HANDLE, THREADINFOCLASS, PVOID, ULONG, PULONG);

using FnWinVerifyTrust = LONG(WINAPI*)(HWND, GUID*, LPVOID);

using FnNtCreateThreadEx = NTSTATUS(NTAPI*)(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, HANDLE, LPTHREAD_START_ROUTINE, LPVOID, ULONG, ULONG_PTR, SIZE_T, SIZE_T, LPVOID);

using FnCloseHandle = BOOL(WINAPI*)(HANDLE);
using FnCreateToolhelp32Snapshot = HANDLE(WINAPI*)(DWORD, DWORD);
using FnThread32First = BOOL(WINAPI*)(HANDLE, LPTHREADENTRY32);
using FnThread32Next = BOOL(WINAPI*)(HANDLE, LPTHREADENTRY32);

using FnNtClose = NTSTATUS(NTAPI*)(HANDLE);

using FnSleep = VOID(WINAPI*)(DWORD);

using FnQueueUserAPC = DWORD(WINAPI*)(PAPCFUNC, HANDLE, ULONG_PTR);

using FnOpenThread = HANDLE(WINAPI*)(DWORD, BOOL, DWORD);

using FnGetCurrentThreadId = DWORD(WINAPI*)(VOID);
using FnGetThreadId = DWORD(WINAPI*)(HANDLE);

using FnGetThreadContext = BOOL(WINAPI*)(HANDLE, LPCONTEXT);

namespace TImportTable {

	namespace TModules {
		inline PVOID NtDll = NULL;
		inline PVOID Kernel32 = NULL;
		inline PVOID WinTrust = NULL;
		bool Initialize();
	}

	namespace TCurrentExecutable {
		inline PVOID pExecutableBase = NULL;
		inline DWORD dwProcessID = NULL;
		inline DWORD dwUniqueThreadID = NULL;
		bool SetupLibrary();
		PTEB GetTeb();
		PPEB GetPeb();
		PVOID GetModuleBase(LPCWSTR ModuleName);
		PVOID GetExportAddress(PVOID pModuleBase, LPCSTR lpProcName, INT Check1, bool bIsMappedImage = false);
	}


	namespace TNtDll
	{
		inline FnNtQuerySystemInformation NtQuerySystemInformation = NULL;
		inline FnNtQueryInformationProcess NtQueryInformationProcess = NULL;
		inline FnNtQueryVirtualMemory NtQueryVirtualMemory = NULL;
		inline FnNtQuerySection NtQuerySection = NULL;

		inline FnNtQueryIoCompletion NtQueryIoCompletion = NULL;
		inline FnNtQueryVolumeInformationFile NtQueryVolumeInformationFile = NULL;
		inline FnNtQueryDirectoryFile NtQueryDirectoryFile = NULL;
		inline FnNtQueryInformationFile NtQueryInformationFile = NULL;
		inline FnNtQueryBootOptions NtQueryBootOptions = NULL;
		inline FnNtQueryBootEntryOrder NtQueryBootEntryOrder = NULL;
		inline FnNtQuerySecurityObject NtQuerySecurityObject = NULL;
		inline FnNtQuerySystemEnvironmentValue NtQuerySystemEnvironmentValue = NULL;
		inline FnNtQueryDriverEntryOrder NtQueryDriverEntryOrder = NULL;
		inline FnNtQueryOpenSubKeysEx NtQueryOpenSubKeysEx = NULL;
		inline FnNtQueryKey NtQueryKey = NULL;
		inline FnNtQueryOpenSubKeys NtQueryOpenSubKeys = NULL;
		inline FnNtQueryValueKey NtQueryValueKey = NULL;
		inline FnNtQueryPerformanceCounter NtQueryPerformanceCounter = NULL;
		inline FnNtQueryInformationToken NtQueryInformationToken = NULL;
		inline FnNtQuerySystemTime NtQuerySystemTime = NULL;
		inline FnNtCreateThreadEx NtCreateThreadEx = NULL;
		inline FnNtQueryInformationThread NtQueryInformationThread = NULL;

		inline FnNtClose NtClose = NULL;
	}

	namespace TKernel32 {
		inline FnLoadLibraryA LoadLibrayA = NULL;
		inline FnGetModuleHandleA GetModuleHandleA = NULL;
		inline FnCloseHandle  CloseHandle = NULL;
		inline FnCreateToolhelp32Snapshot CreateToolhelp32Snapshot;
		inline FnThread32First Thread32First;
		inline FnThread32Next Thread32Next;
		inline FnSleep Sleep;
		inline FnQueueUserAPC QueueUserAPC;
		inline FnOpenThread OpenThread;
		inline FnGetCurrentThreadId GetCurrentThreadId;
		inline FnGetThreadId GetThreadId;
		inline FnGetThreadContext GetThreadContext;
	}

	namespace TWinTrust {
		inline FnWinVerifyTrust WinVerifyTrust = NULL;
	}

}
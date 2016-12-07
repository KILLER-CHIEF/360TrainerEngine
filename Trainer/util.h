#pragma once

#ifndef UTIL_H
#define UTIL_H

#include <xtl.h>
#include <xbdm.h>
#include "XexLoadImage.h"
#include "KernelExports.h"


#ifdef __cplusplus
extern "C" {
#endif
	//   UINT32 __stdcall XexGetModuleHandle(char* module, PVOID hand);
	//   UINT32 __stdcall XexGetProcedureAddress(UINT32 hand ,UINT32, PVOID);
#ifdef __cplusplus
}
#endif

#define setmemdm(addr, data) { DWORD d = data; DmSetMemory((LPVOID)addr, 4, &d, NULL); }


UINT32 __declspec() HvxSetState(UINT32 mode);
#define PROTECT_OFF		0
#define PROTECT_ON		1
#define SET_PROT_OFF	2
#define SET_PROT_ON		3


void Mount(char* dev, char* mnt);

#define __isync()		__emit(0x4C00012C)

#define doSync(addr) \
	do { \
	__dcbst(0, addr); \
	__sync(); \
	__isync(); \
	} while (0)

#define doLightSync(addr) \
	do { \
	__dcbst(0, addr); \
	__sync(); \
	} while (0)

DWORD resolveFunct(char* modname, DWORD ord);


VOID hookFunctionStart(PDWORD addr, PDWORD saveStub, PDWORD oldData, DWORD dest);
VOID unhookFunctionStart(PDWORD addr, PDWORD oldData);
DWORD relinkGPLR(int offset, PDWORD saveStubAddr, PDWORD orgAddr);
VOID patchInJump(DWORD* addr, DWORD dest, BOOL linked);


DWORD makeBranch(DWORD branchAddr, DWORD destination, BOOL linked=false);



typedef void (*XAMLOADLAUNCHTITLEEX)(char* szBootTitle, char* szBootPath, char* szBootCmdLine, DWORD);

//XAMLOADLAUNCHTITLEEX XamLoaderLaunchTitleEx = (XAMLOADLAUNCHTITLEEX)resolveFunct("xam.xex", 421);

void swap_endian(BYTE* src, DWORD size);

enum _KPROC_TYPE {
	PROC_IDLE = 0,
	PROC_USER = 1,
	PROC_SYSTEM = 2,
	PROC_DEBUG = 3,
};

void LaunchXshell(void);

typedef struct _XDASHLAUNCHDATA {
	DWORD dwVersion;
	DWORD dwCommand;
	DWORD dwUserIndex;
	BYTE reserved;
} XDASHLAUNCHDATA, *PXDASHLAUNCHDATA;

//DMHRAPI DmSetMemory(LPVOID lpbAddr, DWORD cb, LPCVOID lpbBuf, LPDWORD pcbRet);
//lpbAddr = address
//cb = size
//lpbBuf = patch data
//pcbRet = return?




#endif
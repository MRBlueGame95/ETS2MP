/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Shared\Memory
 * Licence     : See LICENSE in the top level directory
 * File		   : Memory.h
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#pragma once

#ifdef _WIN32
#include <Windows.h>
#endif

struct sUnknown {};
#define MEMPAD(name,size) BYTE name[size]

class Memory
{
public:
	static void		UnprotectSegment(const char * szName);
	static DWORD	Unprotect(DWORD dwAddress, int iSize);
	static void		Reprotect(DWORD dwAddress, int iSize, DWORD dwOldProtect);

	static void 	JumpHook(DWORD dwFrom, DWORD dwTo);

	static void		CallHook(DWORD dwFrom, DWORD dwTo);

	static void		ReturnHook(DWORD dwAddress);

	static void		NopHook(DWORD dwAddress, int iSize);
};
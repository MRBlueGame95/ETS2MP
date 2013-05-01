/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Shared\Utils
 * Licence     : See LICENSE in the top level directory
 * File		   : SharedUtils.h
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#pragma once

#include <string>
#include <sys/stat.h>

#include <Windows.h>

// Move This!
#define SAFE_DELETE(d) if(d) { delete d; d = NULL; }
#define DLL_EXPORT extern "C" __declspec(dllexport)

#define STRING2(x) #x
#define STRING(x) STRING2(x)
// Mode This!

namespace SharedUtils
{
	const char *				GetAbsolutePath(const char *szFile);

	namespace Injecting
	{
		enum eState
		{
			SUCCEED,
			FAILED
		};
		eState						LibraryIntoProcess(const char * szLibraryPath, HANDLE hProcess);
	};	

	namespace Registry
	{
		bool						Read(HKEY hKeyLocation, const char * szLocation, const char * szRow, const char *szBuffer, DWORD dwSize);
		bool						Write(HKEY hKeyLocation, const char * szSubKey, const char * szKey, const char * szData, DWORD dwSize);
	};

	namespace Protection
	{
		static void					InstallAntyDebugger()
		{
			// MS Debuger
			char dbgState = 0;
			_asm {
				mov eax, fs:[30h]
				mov al, [eax+2h]
				mov dbgState,al
			}

			// TODO Support other debbugers

			if(dbgState)
				ExitProcess(0);			
		}
	};
};
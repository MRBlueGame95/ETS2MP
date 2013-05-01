/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Shared\Libraries
 * Licence     : See LICENSE in the top level directory
 * File		   : CLibrary.h
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#pragma once

#ifdef _WIN32
#include <Windows.h>
#else
#include <dlfcn.h>
#endif
#include <stdio.h>

class CLibrary
{
private:
	void * m_pLibrary;

public:
	CLibrary();
	~CLibrary();

	bool   Load(const char * szPath);
	bool   Unload();
	void * GetProcedureAddress(const char * szProcedureName);
};
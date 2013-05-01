/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : CGameVars.h
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#pragma once

struct Var // sizeof(288)
{
	char * szVarName;
	// TODO
};

class CGameVars
{
private:
	static Var * GetVarible(const char * szVarName);
	static int Refresh(Var * pVar);
public:
	static void StoreCustomVars();

	static bool Set(const char * szVarName, DWORD dwValue);
	// TODO Get
};
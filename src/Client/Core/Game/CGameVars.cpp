/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : CGameVars.cpp
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
// NOTE: Please dont use this class!
#include <Includes.h>

DWORD CVars__Refresh = 0x71FF10;
DWORD CVars__SetValue = 0x71FF80;
DWORD VAR_VarsArray = 0xA90754;
//DWORD CVars__Get = 0x

void CGameVars::StoreCustomVars()
{
	CLogger::Debugf("Building-in multiplayer cvars...");
	//Set("g_developer", 1);
	//Set("g_console", 1);
	//GetVarible("g_developer");

	CLogger::Debugf("Multiplayer cvars builded!");
}

bool CGameVars::Set(const char * szVarName, DWORD dwValue)
{
	Var * pVar = GetVarible(szVarName);
	if(pVar)
	{
		CLogger::Debugf("Varible name: %s ", pVar->szVarName);
		int iReturn = 0;
		_asm
		{
			push dwValue
			mov ecx, pVar
			call CVars__SetValue
			movzx edx, al
			mov iReturn, edx
		}
		return true;
	}
	return false;
}

Var * CGameVars::GetVarible(const char * szVarName)
{
	if(!strcmp(szVarName, "g_console"))
	{
		return (Var*)(*(BYTE*)0xA62C50);
	}
	return NULL;
}

int CGameVars::Refresh(Var * pVar)
{
	int iReturn = -1;
	_asm
	{
		push 0 ; unknown attribute
		mov eax, pVar
		call CVars__Refresh
		mov iReturn, esp
	}
	return iReturn;
}
/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : CConsole.cpp
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>,
 *
 ***************************************************************/
#include <Includes.h>

void _declspec(naked) CConsole::Write(char *, ...)
{
	_asm
	{
		jmp CGameOffsets::FUNC_CConsole__Write
	}
}
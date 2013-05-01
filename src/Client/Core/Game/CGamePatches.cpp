/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : CGamePatches.cpp
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#include <Includes.h>

bool CGamePatches::Initialize()
{
	// Disable tutorial
	// TODO

	// Disable PDA rendering (For test reason)
	// TODO

	// Disable info box rendering
	// TODO

	// Change saves directory
	// todo
	
	// Disable mods
	*(BYTE*)0x9D99C4 = 0;
	*(BYTE*)0x99284C = 0;

	return true;
}
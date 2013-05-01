/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : CGameOffsets.h
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#pragma once

enum eGameVersions
{
	ETS2_105 = 0x0105,
	ETS2_111 = 0x0111,
	ETS2_113 = 0x0113,
	ETS2_125 = 0x0125,
	ETS2_1251 = 0x1251,
	ETS2_131  = 0x131,
	ETS2_UNK = 0xFFFF
};

class CGameOffsets
{
private:
	static eGameVersions m_GameVersion;
public:
	static bool Initialize();
	static eGameVersions GetGameVersion();

	static unsigned long VAR_GamePtr;
	
	static unsigned long FUNC_CConsole__Write;
};
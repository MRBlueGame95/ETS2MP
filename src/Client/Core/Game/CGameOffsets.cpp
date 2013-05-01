/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : CGameOffsets.cpp
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#include <Includes.h>

unsigned long CGameOffsets::VAR_GamePtr = NULL;

unsigned long CGameOffsets::FUNC_CConsole__Write = 0;

eGameVersions CGameOffsets::m_GameVersion = ETS2_UNK;

bool CGameOffsets::Initialize()
{
	// Unprotect all memory segments
	Memory::UnprotectSegment(".rdata");
	Memory::UnprotectSegment(".text");

	// Supported
	eGameVersions supported = ETS2_131;

	// Game version checking
	DWORD dwCheck = *(DWORD *)0x663730;
	switch(dwCheck)
	{
	case 0x2815FF53:
		{
			// 53 FF 15 28
			m_GameVersion = ETS2_105;
		} break;
	case 0x5608EC83:
		{
			// 83 EC 08 56
			m_GameVersion = ETS2_111;
		} break;
	case 0xB8140D8B:
		{
			// 8B 0D 14 B8
			m_GameVersion = ETS2_113;
		} break;
	case 0x24448D00:
		{
			// 00 8D 44 24 (1.2.5 & 1.2.5.1)
			m_GameVersion = ETS2_1251;// ETS2_125 too :)

			VAR_GamePtr = 0xA6B838;

			FUNC_CConsole__Write = 0x5EE0D0;
		} break;
	case 0x100FF330:
		{
			// 30 F3 0F  10
			m_GameVersion = ETS2_131;

			VAR_GamePtr = 0xAA7A34;

			FUNC_CConsole__Write = 0x605900;
		} break;
	default:
		{
			m_GameVersion = ETS2_UNK;
		} break;
	}

	if(m_GameVersion != supported)
	{
		return false;
	}

	return true;
}

eGameVersions CGameOffsets::GetGameVersion()
{
	return m_GameVersion;
}
/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : EconomyETS2.h
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>,
 *
 ***************************************************************/
#pragma once

class EconomyETS2
{
public:
	MEMPAD(pad1, 0x28);		// 000-028
	CameraETS2 * camera;	// 028-02C
	MEMPAD(pad2, 0x4);		// 02C-030
	TruckETS2 * truck;		// 030-034
	MEMPAD(pad3, 0x64);		// 034-098
	DWORD time;				// 098-09C

	// TODO sizeof
};
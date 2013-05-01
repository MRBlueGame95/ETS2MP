/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : TruckETS2.h
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>,
 *
 ***************************************************************/
#pragma once

class UnknownTruckStuffETS2
{
public:
	MEMPAD(pad1, 72);
	char * plate;
};

class TruckETS2
{
public:
	MEMPAD(pad1, 64);//00-64
	UnknownTruckStuffETS2 * unk;//64-68
	// TODO sizeof
};
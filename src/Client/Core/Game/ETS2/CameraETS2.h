/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : CameraETS2.h
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>,
 *
 ***************************************************************/
#pragma once

struct CameraETS2VTable
{
	DWORD ScalarDestructor; // 000-004
};

class CameraETS2//0xA6B844 - i think it's VAR_Camera
{
public:
	CameraETS2VTable * pVTable;		// 000-004

	// TODO
};
/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : CSCSArchive.h
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#pragma once

/*
 * ========================================
 * ============= File struct ==============
 * ========================================
 * = Name		    || Size (in bytes)	  =
 * ========================================
 * = SCSHeader      || 20				  =
 * = SCSArchiveInfo || ?				  =
 * ========================================
 */
struct SCSHeader 
{
	char cId[3]; // 0 = S / 1 = C / 2 = S
	// TODO
	MEMPAD(pad1,0x11);
	// sizeof(SCSHeader) = 0x14
};

struct SCSArchiveInfo
{
	//TODO
};
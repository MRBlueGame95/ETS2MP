/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Shared
 * Licence     : See LICENSE in the top level directory
 * File		   : Version.h
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#pragma once

#define NET_VERSION 0x01
#define VERSION 0x01

#define PROJECT_NAME				"Euro Truck Simulator 2 Multiplayer"
#define PROJECT_SHORT				"ETS2-MP"
#define PROJECT_VERSION				"0.1 Development Preview"
#ifdef DEBUG
	#define PROJECT_STRING				PROJECT_NAME" "PROJECT_VERSION" - Debug"
#else
	#define PROJECT_STRING				PROJECT_NAME" "PROJECT_VERSION
#endif
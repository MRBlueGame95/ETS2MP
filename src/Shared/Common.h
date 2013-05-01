/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Shared
 * Licence     : See LICENSE in the top level directory
 * File		   : Common.h
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#pragma once

#define GAME_NAME					"Euro Truck Simulator 2"

#ifdef DEBUG
#define BASE_LIBRARY				"Client_d.dll"
#else
#define BASE_LIBRARY				"Client.dll"
#endif

#define PROJECT_REGISTRY_KEY		"Software\\"PROJECT_NAME
#define MOD_SUPPORTED_VERSIONS	    "1.2.5"
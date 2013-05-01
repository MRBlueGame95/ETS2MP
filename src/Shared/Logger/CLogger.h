/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Shared\Logger
 * Licence     : See LICENSE in the top level directory
 * File		   : CLogger.h
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#pragma once

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

class CLogger
{
private:
	static bool m_bInitialized;
	static FILE * m_LogFile;
public:
	static void Init(const char * szFile);

	static void Close();

	static void Printf(const char * szString, ...);

	static void Debugf(const char * szString, ...);
};
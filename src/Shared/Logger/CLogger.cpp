/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Shared\Logger
 * Licence     : See LICENSE in the top level directory
 * File		   : CLogger.cpp
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#include "CLogger.h"

bool CLogger::m_bInitialized = false;
FILE * CLogger::m_LogFile = NULL;

void CLogger::Init(const char * szFile)
{
	if(m_bInitialized)
		return;

	m_LogFile = fopen(szFile,"a+");
	if(m_LogFile)
		m_bInitialized = true;
}

void CLogger::Close()
{
	if(!m_bInitialized)
		return;

	if(m_LogFile)
		fclose(m_LogFile);
}

void CLogger::Printf(const char * szString, ...)
{
	if(!m_bInitialized)
		return;

	char szBuffer[1024];

	va_list vArgs;
	va_start(vArgs,szString);
	vsprintf(szBuffer,szString,vArgs);
	va_end(vArgs);
	
	sprintf(szBuffer,"%s\n",szBuffer);

	fprintf(m_LogFile,szBuffer);
	fflush(m_LogFile);
#ifdef DEBUG
	printf(szBuffer);
#endif
}

void CLogger::Debugf(const char * szString, ...)
{
#ifdef DEBUG
	if(!m_bInitialized)
		return;

	char szBuffer[1024];

	va_list vArgs;
	va_start(vArgs,szString);
	vsprintf(szBuffer,szString,vArgs);
	va_end(vArgs);
	sprintf(szBuffer,"%s\n",szBuffer);

	fprintf(m_LogFile,szBuffer);
	printf(szBuffer);
	fflush(m_LogFile);
#endif
}

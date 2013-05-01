/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Shared\Libraries
 * Licence     : See LICENSE in the top level directory
 * File		   : CLibrary.cpp
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#include "CLibrary.h"

CLibrary::CLibrary()
{
	m_pLibrary = NULL;
}

CLibrary::~CLibrary()
{
	if(m_pLibrary)
		Unload();
}

bool CLibrary::Load(const char * szPath)
{
	if(!m_pLibrary)
	{
		char szPaths[MAX_PATH];
		sprintf(szPaths, "%s", szPath);
#ifdef WIN32
		m_pLibrary = LoadLibrary(szPaths);
#else
		m_pLibrary = dlopen(szPaths, RTLD_LAZY);
#endif

		if(!m_pLibrary)
		{
			return false;
		}

		return true;
	}

	return false;
}

bool CLibrary::Unload()
{
	if(m_pLibrary)
	{
#ifdef WIN32
		FreeLibrary((HMODULE)m_pLibrary);
#else
		dlclose((HMODULE)m_pLibrary);
#endif
		m_pLibrary = NULL;
		return true;
	}

	return false;
}

void * CLibrary::GetProcedureAddress(const char * szProcedureName)
{
	if(m_pLibrary)
	{
		void * pProcedureAddress = NULL;
#ifdef WIN32
		pProcedureAddress = (void *)GetProcAddress((HMODULE)m_pLibrary, szProcedureName);
#else
		pProcedureAddress = (void *)dlsym((HMODULE)m_pLibrary, szProcedureName);
#endif
		return pProcedureAddress;
	}

	return NULL;
}
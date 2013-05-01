/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : CDirect3D9Hook.cpp
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#include <Includes.h>

CDirect3D9Hook::Direct3DCreate9_t CDirect3D9Hook::m_pfnDirect3DCreate9;
CDirect3D9Hook::Direct3DCreate9Ex_t CDirect3D9Hook::m_pfnDirect3DCreate9Ex;

bool CDirect3D9Hook::m_bHookInstalled = false;

bool CDirect3D9Hook::Install()
{
	if(!m_bHookInstalled)
	{      
		CLogger::Debugf("Installing Direct3D9 Hook..");

		m_pfnDirect3DCreate9 = reinterpret_cast<Direct3DCreate9_t>(DetourFunction(DetourFindFunction ("D3D9.DLL", "Direct3DCreate9"),  reinterpret_cast<PBYTE>(Direct3DCreate9_Hook)));
		m_pfnDirect3DCreate9Ex = reinterpret_cast<Direct3DCreate9Ex_t>(DetourFunction(DetourFindFunction ("D3D9.DLL", "Direct3DCreate9Ex"),  reinterpret_cast<PBYTE>(Direct3DCreate9Ex_Hook)));

		CLogger::Debugf("Direct3D9 Hook applied!");

		m_bHookInstalled = true;
        return true;
    }
    return false;
}

void CDirect3D9Hook::Uninstall()
{
	if(m_bHookInstalled)
    {
        if ( m_pfnDirect3DCreate9 )
		{
			DetourRemove ( reinterpret_cast < PBYTE > ( m_pfnDirect3DCreate9 ), reinterpret_cast < PBYTE > ( Direct3DCreate9_Hook ) );
		}
		
		if ( m_pfnDirect3DCreate9Ex )
		{
			DetourRemove ( reinterpret_cast < PBYTE > ( m_pfnDirect3DCreate9Ex ), reinterpret_cast < PBYTE > ( Direct3DCreate9Ex_Hook ) );
		}
                        
        m_bHookInstalled = false;
    }
}

IDirect3D9 * WINAPI CDirect3D9Hook::Direct3DCreate9_Hook(UINT SDKVersion)
{
    IDirect3D9 * pD3D = m_pfnDirect3DCreate9(SDKVersion);
    return (!pD3D ? NULL : new IDirect3D9Proxy(pD3D));
}

HRESULT WINAPI CDirect3D9Hook::Direct3DCreate9Ex_Hook(UINT SDKVersion, IDirect3D9Ex ** ppD3D)
{
	HRESULT hr = m_pfnDirect3DCreate9Ex(SDKVersion, ppD3D);
     
	if(ppD3D)
	{
		*ppD3D = new IDirect3D9ProxyEx(*ppD3D);
	}

	return hr;
}
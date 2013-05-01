/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : CDirect3D9Hook.h
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#pragma once

class CDirect3D9Hook
{
private:
	typedef					IDirect3D9 * (WINAPI * Direct3DCreate9_t)(UINT);
	typedef					HRESULT (WINAPI * Direct3DCreate9Ex_t)(UINT, IDirect3D9Ex **);
	static bool					m_bHookInstalled;
	static Direct3DCreate9_t m_pfnDirect3DCreate9;
	static Direct3DCreate9Ex_t m_pfnDirect3DCreate9Ex;
	static IDirect3D9 * WINAPI Direct3DCreate9_Hook(UINT SDKVersion);
	static HRESULT	WINAPI	Direct3DCreate9Ex_Hook(UINT SDKVersion, IDirect3D9Ex ** ppD3D);
	static HINSTANCE			h_dllHandle;	
public:
	static bool				Install();
	static void				Uninstall();
};
/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : CDirectInput8Hook.cpp
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#include <Includes.h>

DirectInput8Create_t			CDirectInput8Hook::m_pDirectInput8Create = NULL;
DirectInputCreateEx_t			CDirectInput8Hook::m_pDirectInputCreateEx = NULL;
XInputGetState_t				CDirectInput8Hook::m_pXInputGetState = NULL;

bool							CDirectInput8Hook::m_bInstalled = false;

bool CDirectInput8Hook::Install()
{
	if(!m_bInstalled)
	{
		m_pXInputGetState = (XInputGetState_t) DetourFunction( DetourFindFunction( "xinput1_3.dll", "XInputGetState" ), (PBYTE)XInputGetState__Hook );
		m_pDirectInput8Create = ( DirectInput8Create_t ) DetourFunction( DetourFindFunction( "dinput8.dll", "DirectInput8Create" ), (PBYTE)DirectInput8Create__Hook );
		m_pDirectInputCreateEx = ( DirectInputCreateEx_t ) DetourFunction( DetourFindFunction( "dinput.dll", "DirectInputCreateEx" ), (PBYTE)DirectInputCreateEx__Hook );	

		m_bInstalled = true;
		return true;
	}
	return false;
}

void CDirectInput8Hook::Uninstall( )
{
	if( !m_bInstalled )
		return;

	DetourRemove( (PBYTE)m_pDirectInput8Create, (PBYTE)DirectInput8Create__Hook );

	m_bInstalled = false;
}

HRESULT WINAPI CDirectInput8Hook::DirectInput8Create__Hook( HINSTANCE hInst, DWORD dwVersion, REFIID riidltf, LPVOID * ppvOut, LPUNKNOWN punkOuter )
{
	HRESULT hResult = m_pDirectInput8Create( hInst, dwVersion, riidltf, ppvOut, punkOuter );

	if( SUCCEEDED( hResult ) )
	{
		IDirectInput8 * pInput = (IDirectInput8 *)*ppvOut;
		*ppvOut = new IDirectInput8Proxy( pInput );
	}

	return hResult;
}

DWORD WINAPI CDirectInput8Hook::XInputGetState__Hook(DWORD dwUserIndex, XINPUT_STATE * pState)
{
	DWORD dwResult = m_pXInputGetState(dwUserIndex, pState);

	if(!CClient::GetInstance().getControls())
	{
		memset(pState, 0, sizeof(XINPUT_STATE));
	}
	return dwResult;
}

HRESULT WINAPI CDirectInput8Hook::DirectInputCreateEx__Hook( HINSTANCE hInst, DWORD dwVersion, REFIID riidltf, LPVOID * ppvOut, LPUNKNOWN punkOuter )
{
	// NOTE: It's old function and not finished yet (TODO)
	HRESULT hResult = m_pDirectInputCreateEx( hInst, dwVersion, riidltf, ppvOut, punkOuter );	
	return hResult;
}
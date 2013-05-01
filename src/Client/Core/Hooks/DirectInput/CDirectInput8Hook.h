/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : CDirectInput8Hook.h
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#pragma once

typedef HRESULT	( WINAPI * DirectInput8Create_t )( HINSTANCE, DWORD, REFIID, LPVOID *, LPUNKNOWN );
typedef HRESULT ( WINAPI  * DirectInputCreateEx_t)(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID *ppvOut, LPUNKNOWN punkOuter);
typedef DWORD  (WINAPI * XInputGetState_t)(DWORD dwUserIndex, XINPUT_STATE * pState);

class CDirectInput8Hook
{
private:
	static bool							m_bInstalled;
	static DirectInput8Create_t			m_pDirectInput8Create;
	static DirectInputCreateEx_t		m_pDirectInputCreateEx;
    static XInputGetState_t				m_pXInputGetState;

	static HRESULT WINAPI				DirectInput8Create__Hook( HINSTANCE hInst, DWORD dwVersion, REFIID riidltf, LPVOID * ppvOut, LPUNKNOWN punkOuter );
	static HRESULT WINAPI				DirectInputCreateEx__Hook( HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID *ppvOut, LPUNKNOWN punkOuter ) ;
	static DWORD WINAPI					XInputGetState__Hook(DWORD dwUserIndex, XINPUT_STATE * pState);
public:
	static bool							Install( );
	static void							Uninstall( );

};
/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : IDirectInput8Proxy.cpp
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#include <Includes.h>

IDirectInput8Proxy::IDirectInput8Proxy(IDirectInput8 * dinput)
{
	m_pDevice = dinput;
}

HRESULT STDMETHODCALLTYPE IDirectInput8Proxy::QueryInterface(REFIID riid, LPVOID * ppvObj)
{
	return m_pDevice->QueryInterface(riid, ppvObj);
}

ULONG STDMETHODCALLTYPE IDirectInput8Proxy::AddRef()
{
	return m_pDevice->AddRef();
}

ULONG STDMETHODCALLTYPE IDirectInput8Proxy::Release()
{
	ULONG uRet = m_pDevice->Release();

	if ( uRet == 0 )
		delete this;

	return uRet;
}

HRESULT STDMETHODCALLTYPE IDirectInput8Proxy::CreateDevice(REFGUID rguid, LPDIRECTINPUTDEVICE8A * lplpDirectInputDevice, LPUNKNOWN pUknOuter)
{
	// Create the dinput device
	HRESULT hResult = m_pDevice->CreateDevice( rguid, lplpDirectInputDevice, pUknOuter );

	if ( hResult == DI_OK )
	{
		// Get the device type
        eDIDeviceType type = DIDEVICE_TYPE_UNKNOWN;

        if(rguid == GUID_SysMouse)
			type = DIDEVICE_TYPE_MOUSE;
		else if(rguid == GUID_SysKeyboard)
            type = DIDEVICE_TYPE_KEYBOARD;
        else if(rguid == GUID_Joystick)
			type = DIDEVICE_TYPE_JOYSTICK;

		// Device created; Feed the application our proxy interface
		*lplpDirectInputDevice = new IDirectInputDevice8Proxy( *lplpDirectInputDevice, type );
	}

	return hResult;
}

HRESULT STDMETHODCALLTYPE IDirectInput8Proxy::EnumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACKA lpCallback, LPVOID pvRef, DWORD dwFlags)
{
	return m_pDevice->EnumDevices(dwDevType, lpCallback, pvRef, dwFlags);
}

HRESULT STDMETHODCALLTYPE IDirectInput8Proxy::GetDeviceStatus(REFGUID rguidInstance)
{
	return m_pDevice->GetDeviceStatus(rguidInstance);
}

HRESULT STDMETHODCALLTYPE IDirectInput8Proxy::RunControlPanel(HWND hwndOwner, DWORD dwFlags)
{
	return m_pDevice->RunControlPanel(hwndOwner, dwFlags);
}

HRESULT STDMETHODCALLTYPE IDirectInput8Proxy::Initialize(HINSTANCE hinst, DWORD dwVersion)
{
	return m_pDevice->Initialize(hinst, dwVersion);
}

HRESULT STDMETHODCALLTYPE IDirectInput8Proxy::FindDevice(REFGUID rguidClass, LPCSTR ptszName, LPGUID pguidInstance)
{
	return m_pDevice->FindDevice(rguidClass, ptszName, pguidInstance);
}

HRESULT STDMETHODCALLTYPE IDirectInput8Proxy::EnumDevicesBySemantics(LPCSTR ptszUserName, LPDIACTIONFORMATA lpdiActionFormat, LPDIENUMDEVICESBYSEMANTICSCBA lpCallback, LPVOID pvRef, DWORD dwFlags)
{
	return m_pDevice->EnumDevicesBySemantics(ptszUserName, lpdiActionFormat, lpCallback, pvRef, dwFlags);
}

HRESULT STDMETHODCALLTYPE IDirectInput8Proxy::ConfigureDevices(LPDICONFIGUREDEVICESCALLBACK lpdiCallback, LPDICONFIGUREDEVICESPARAMSA lpdiCDParams, DWORD dwFlags, LPVOID pvRefData)
{
	return m_pDevice->ConfigureDevices(lpdiCallback, lpdiCDParams, dwFlags, pvRefData);
}
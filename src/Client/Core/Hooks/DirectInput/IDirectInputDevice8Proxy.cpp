/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : IDirectInputDevice8Proxy.cpp
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#include <Includes.h>

IDirectInputDevice8Proxy::IDirectInputDevice8Proxy(IDirectInputDevice8 * pDevice, eDIDeviceType DeviceType)
{
	m_pDevice = pDevice;
}

HRESULT STDMETHODCALLTYPE IDirectInputDevice8Proxy::QueryInterface(REFIID riid, LPVOID * ppvObj)
{
	return m_pDevice->QueryInterface(riid, ppvObj);
}

ULONG STDMETHODCALLTYPE IDirectInputDevice8Proxy::AddRef()
{
	return m_pDevice->AddRef();
}

ULONG STDMETHODCALLTYPE IDirectInputDevice8Proxy::Release()
{
	ULONG uRet = m_pDevice->Release( );

	if ( uRet == 0 )
		delete this;

	return uRet;
}

HRESULT STDMETHODCALLTYPE IDirectInputDevice8Proxy::GetCapabilities(LPDIDEVCAPS p0)
{
	return m_pDevice->GetCapabilities(p0);
}

HRESULT STDMETHODCALLTYPE IDirectInputDevice8Proxy::EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACKA p0, LPVOID p1, DWORD p2)
{
	return m_pDevice->EnumObjects(p0, p1, p2);
}

HRESULT STDMETHODCALLTYPE IDirectInputDevice8Proxy::GetProperty(REFGUID rguid, LPDIPROPHEADER p1)
{
	return m_pDevice->GetProperty(rguid, p1);
}

HRESULT STDMETHODCALLTYPE IDirectInputDevice8Proxy::SetProperty(REFGUID rguid, LPCDIPROPHEADER p1)
{
	return m_pDevice->SetProperty(rguid, p1);
}

HRESULT STDMETHODCALLTYPE IDirectInputDevice8Proxy::Acquire()
{
	return m_pDevice->Acquire();
}

HRESULT STDMETHODCALLTYPE IDirectInputDevice8Proxy::Unacquire()
{
	return m_pDevice->Unacquire();
}

HRESULT STDMETHODCALLTYPE IDirectInputDevice8Proxy::GetDeviceState(DWORD p0, LPVOID p1)
{
	HRESULT hResult = m_pDevice->GetDeviceState( p0, p1 );

	if(!CClient::GetInstance().getControls())
	{
		memset(p1, 0, p0);
	}
	return hResult;
}

HRESULT STDMETHODCALLTYPE IDirectInputDevice8Proxy::GetDeviceData(DWORD p0, LPDIDEVICEOBJECTDATA p1, LPDWORD p2, DWORD p3)
{
	HRESULT hr = m_pDevice->GetDeviceData( p0, p1, p2, p3 );

	if(!CClient::GetInstance().getControls())
	{
		 memset(p1, 0, (p0 * (*p2)));
	}
	return hr;
}

HRESULT STDMETHODCALLTYPE IDirectInputDevice8Proxy::SetDataFormat(LPCDIDATAFORMAT p0)
{
	return m_pDevice->SetDataFormat(p0);
}

HRESULT STDMETHODCALLTYPE IDirectInputDevice8Proxy::SetEventNotification(HANDLE p0)
{
	return m_pDevice->SetEventNotification(p0);
}

HRESULT STDMETHODCALLTYPE IDirectInputDevice8Proxy::SetCooperativeLevel(HWND p0, DWORD p1)
{
	return m_pDevice->SetCooperativeLevel(p0, p1);
}

HRESULT STDMETHODCALLTYPE IDirectInputDevice8Proxy::GetObjectInfo(LPDIDEVICEOBJECTINSTANCEA p0, DWORD p1, DWORD p2)
{
	return m_pDevice->GetObjectInfo(p0, p1, p2);
}

HRESULT STDMETHODCALLTYPE IDirectInputDevice8Proxy::GetDeviceInfo(LPDIDEVICEINSTANCEA p0)
{
	return m_pDevice->GetDeviceInfo(p0);
}

HRESULT STDMETHODCALLTYPE IDirectInputDevice8Proxy::RunControlPanel(HWND p0, DWORD p1)
{
	return m_pDevice->RunControlPanel(p0, p1);
}

HRESULT STDMETHODCALLTYPE IDirectInputDevice8Proxy::Initialize(HINSTANCE p0, DWORD p1, REFGUID rguid)
{
	return m_pDevice->Initialize(p0, p1, rguid);
}

HRESULT STDMETHODCALLTYPE IDirectInputDevice8Proxy::CreateEffect(REFGUID rguid, LPCDIEFFECT p1, LPDIRECTINPUTEFFECT * p2, LPUNKNOWN p3)
{
	return m_pDevice->CreateEffect(rguid, p1, p2, p3);
}

HRESULT STDMETHODCALLTYPE IDirectInputDevice8Proxy::EnumEffects(LPDIENUMEFFECTSCALLBACKA p0, LPVOID p1, DWORD p2)
{
	return m_pDevice->EnumEffects(p0, p1, p2);
}

HRESULT STDMETHODCALLTYPE IDirectInputDevice8Proxy::GetEffectInfo(LPDIEFFECTINFOA p0, REFGUID rguid)
{
	return m_pDevice->GetEffectInfo(p0, rguid);
}

HRESULT STDMETHODCALLTYPE IDirectInputDevice8Proxy::GetForceFeedbackState(LPDWORD p0)
{
	return m_pDevice->GetForceFeedbackState(p0);
}

HRESULT STDMETHODCALLTYPE IDirectInputDevice8Proxy::SendForceFeedbackCommand(DWORD p0)
{
	return m_pDevice->SendForceFeedbackCommand(p0);
}

HRESULT STDMETHODCALLTYPE IDirectInputDevice8Proxy::EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK p0, LPVOID p1, DWORD p2)
{
	return m_pDevice->EnumCreatedEffectObjects(p0, p1, p2);
}

HRESULT STDMETHODCALLTYPE IDirectInputDevice8Proxy::Escape(LPDIEFFESCAPE p0)
{
	return m_pDevice->Escape(p0);
}

HRESULT STDMETHODCALLTYPE IDirectInputDevice8Proxy::Poll()
{
	return m_pDevice->Poll();
}

HRESULT STDMETHODCALLTYPE IDirectInputDevice8Proxy::SendDeviceData(DWORD p0, LPCDIDEVICEOBJECTDATA p1, LPDWORD p2, DWORD p3)
{
	return m_pDevice->SendDeviceData(p0, p1, p2, p3);
}

HRESULT STDMETHODCALLTYPE IDirectInputDevice8Proxy::EnumEffectsInFile(LPCSTR p0, LPDIENUMEFFECTSINFILECALLBACK p1, LPVOID p2, DWORD p3)
{
	return m_pDevice->EnumEffectsInFile(p0, p1, p2, p3);
}

HRESULT STDMETHODCALLTYPE IDirectInputDevice8Proxy::WriteEffectToFile(LPCSTR p0, DWORD p2, LPDIFILEEFFECT p3, DWORD p4)
{
	return m_pDevice->WriteEffectToFile(p0, p2, p3, p4);
}

HRESULT STDMETHODCALLTYPE IDirectInputDevice8Proxy::BuildActionMap(LPDIACTIONFORMATA p0, LPCSTR p1, DWORD p2)
{
	return m_pDevice->BuildActionMap(p0, p1, p2);
}

HRESULT STDMETHODCALLTYPE IDirectInputDevice8Proxy::SetActionMap(LPDIACTIONFORMATA p0, LPCSTR p1, DWORD p2)
{
	return m_pDevice->SetActionMap(p0, p1, p2);
}

HRESULT STDMETHODCALLTYPE IDirectInputDevice8Proxy::GetImageInfo(LPDIDEVICEIMAGEINFOHEADERA p0)
{
	return m_pDevice->GetImageInfo(p0);
}
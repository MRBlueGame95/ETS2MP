/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : IDirect3D9ProxyEx.cpp
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#include <Includes.h>

IDirect3D9ProxyEx::IDirect3D9ProxyEx(IDirect3D9Ex * pD3D)
{
	m_pD3D = pD3D;
}

HRESULT STDMETHODCALLTYPE IDirect3D9ProxyEx::QueryInterface(REFIID riid, void ** ppvObj)
{
	return m_pD3D->QueryInterface(riid, ppvObj);
}

ULONG STDMETHODCALLTYPE IDirect3D9ProxyEx::AddRef()
{
	return m_pD3D->AddRef();
}

ULONG STDMETHODCALLTYPE IDirect3D9ProxyEx::Release()
{
	ULONG uRet = m_pD3D->Release();

	if(uRet == 0)
		delete this;

	return uRet;
}

HRESULT STDMETHODCALLTYPE IDirect3D9ProxyEx::RegisterSoftwareDevice(void * pInitializeFunction)
{
	return m_pD3D->RegisterSoftwareDevice(pInitializeFunction);
}

UINT STDMETHODCALLTYPE IDirect3D9ProxyEx::GetAdapterCount()
{
	return m_pD3D->GetAdapterCount();
}

HRESULT STDMETHODCALLTYPE IDirect3D9ProxyEx::GetAdapterIdentifier(UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER9 * pIdentifier)
{
	return m_pD3D->GetAdapterIdentifier(Adapter, Flags, pIdentifier);
}

UINT STDMETHODCALLTYPE IDirect3D9ProxyEx::GetAdapterModeCount(UINT Adapter, D3DFORMAT Format)
{
	return m_pD3D->GetAdapterModeCount(Adapter, Format);
}

HRESULT STDMETHODCALLTYPE IDirect3D9ProxyEx::EnumAdapterModes(UINT Adapter, D3DFORMAT Format, UINT Mode, D3DDISPLAYMODE* pMode)
{
	return m_pD3D->EnumAdapterModes(Adapter, Format, Mode, pMode);
}

HRESULT STDMETHODCALLTYPE IDirect3D9ProxyEx::GetAdapterDisplayMode(UINT Adapter, D3DDISPLAYMODE* pMode)
{
	return m_pD3D->GetAdapterDisplayMode(Adapter, pMode);
}

HRESULT STDMETHODCALLTYPE IDirect3D9ProxyEx::CheckDeviceType(UINT Adapter, D3DDEVTYPE DevType, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, BOOL bWindowed)
{
	return m_pD3D->CheckDeviceType(Adapter, DevType, AdapterFormat, BackBufferFormat, bWindowed);
}

HRESULT STDMETHODCALLTYPE IDirect3D9ProxyEx::CheckDeviceFormat(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat)
{
	return m_pD3D->CheckDeviceFormat(Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat);
}

HRESULT STDMETHODCALLTYPE IDirect3D9ProxyEx::CheckDeviceMultiSampleType(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType, DWORD * pQualityLevels)
{
	return m_pD3D->CheckDeviceMultiSampleType(Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType, pQualityLevels);
}

HRESULT STDMETHODCALLTYPE IDirect3D9ProxyEx::CheckDepthStencilMatch(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat)
{
	return m_pD3D->CheckDepthStencilMatch(Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat);
}

HRESULT STDMETHODCALLTYPE IDirect3D9ProxyEx::CheckDeviceFormatConversion(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SourceFormat, D3DFORMAT TargetFormat)
{
	return m_pD3D->CheckDeviceFormatConversion(Adapter, DeviceType, SourceFormat, TargetFormat);
}

HRESULT STDMETHODCALLTYPE IDirect3D9ProxyEx::GetDeviceCaps(UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS9* pCaps)
{
	return m_pD3D->GetDeviceCaps(Adapter, DeviceType, pCaps);
}

HMONITOR STDMETHODCALLTYPE IDirect3D9ProxyEx::GetAdapterMonitor(UINT Adapter)
{
	return m_pD3D->GetAdapterMonitor(Adapter);
}

HRESULT STDMETHODCALLTYPE IDirect3D9ProxyEx::CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS * pPresentationParameters, IDirect3DDevice9 ** ppReturnedDeviceInterface)
{
	HRESULT hr = m_pD3D->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);

	CWindowProcess::Install(hFocusWindow);

	// Set window title
	SetWindowText(hFocusWindow,PROJECT_STRING);
	
	if(SUCCEEDED(hr))
	{
		*ppReturnedDeviceInterface = new IDirect3DDevice9Proxy(*ppReturnedDeviceInterface);
	}
	return hr;
}

HRESULT STDMETHODCALLTYPE IDirect3D9ProxyEx::CreateDeviceEx(UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,D3DDISPLAYMODEEX* pFullscreenDisplayMode,IDirect3DDevice9Ex** ppReturnedDeviceInterface)
{
	CWindowProcess::Install(hFocusWindow);

	// Set window title
	SetWindowText(hFocusWindow,PROJECT_STRING);

	HRESULT hr = m_pD3D->CreateDeviceEx(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, pFullscreenDisplayMode, ppReturnedDeviceInterface);
	if(SUCCEEDED(hr))
	{
		*ppReturnedDeviceInterface = new IDirect3DDevice9ProxyEx(*ppReturnedDeviceInterface);
	}
	return hr;
}

UINT STDMETHODCALLTYPE IDirect3D9ProxyEx::GetAdapterModeCountEx(UINT Adapter,CONST D3DDISPLAYMODEFILTER* pFilter )
{
	return m_pD3D->GetAdapterModeCountEx(Adapter, pFilter);
}

HRESULT STDMETHODCALLTYPE IDirect3D9ProxyEx::EnumAdapterModesEx(UINT Adapter,CONST D3DDISPLAYMODEFILTER* pFilter,UINT Mode,D3DDISPLAYMODEEX* pMode)
{
	return m_pD3D->EnumAdapterModesEx(Adapter, pFilter, Mode, pMode);
}

HRESULT STDMETHODCALLTYPE IDirect3D9ProxyEx::GetAdapterDisplayModeEx(UINT Adapter,D3DDISPLAYMODEEX* pMode,D3DDISPLAYROTATION* pRotation)
{
	return m_pD3D->GetAdapterDisplayModeEx(Adapter, pMode, pRotation);
}

HRESULT STDMETHODCALLTYPE IDirect3D9ProxyEx::GetAdapterLUID(UINT Adapter,LUID * pLUID)
{
	return m_pD3D->GetAdapterLUID(Adapter, pLUID);
}
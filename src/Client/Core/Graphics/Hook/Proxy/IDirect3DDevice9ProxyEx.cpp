/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : IDirect3DDevice9ProxyEx.cpp
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#include <Includes.h>

IDirect3DDevice9ProxyEx::IDirect3DDevice9ProxyEx(IDirect3DDevice9Ex *pDevice)
{
	m_pDevice = pDevice;
	CGraphics::Initialize(m_pDevice);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::Present ( CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{
	return m_pDevice->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::QueryInterface(REFIID riid, void** ppvObj)
{
	return m_pDevice->QueryInterface(riid, ppvObj);
}

ULONG __stdcall IDirect3DDevice9ProxyEx::AddRef()
{
	return m_pDevice->AddRef();
}

ULONG __stdcall IDirect3DDevice9ProxyEx::Release()
{
	ULONG uRet = m_pDevice->Release();

	if(uRet == 0)
	{
		delete this;
	}
	return uRet;
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::TestCooperativeLevel()
{
	return m_pDevice->TestCooperativeLevel();
}

UINT __stdcall IDirect3DDevice9ProxyEx::GetAvailableTextureMem()
{
	return m_pDevice->GetAvailableTextureMem();
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::EvictManagedResources()
{
	return m_pDevice->EvictManagedResources();
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetDirect3D(IDirect3D9** ppD3D9)
{
	return m_pDevice->GetDirect3D(ppD3D9);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetDeviceCaps(D3DCAPS9* pCaps)
{
	return m_pDevice->GetDeviceCaps(pCaps);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetDisplayMode(UINT iSwapChain, D3DDISPLAYMODE* pMode)
{
	return m_pDevice->GetDisplayMode(iSwapChain, pMode);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS *pParameters)
{
	return m_pDevice->GetCreationParameters(pParameters);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetCursorProperties(UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9* pCursorBitmap)
{
	return m_pDevice->SetCursorProperties(XHotSpot, YHotSpot, pCursorBitmap);
}

void __stdcall IDirect3DDevice9ProxyEx::SetCursorPosition(int X, int Y, DWORD Flags)
{
	m_pDevice->SetCursorPosition(X, Y, Flags);
}

BOOL __stdcall IDirect3DDevice9ProxyEx::ShowCursor(BOOL bShow)
{
	return m_pDevice->ShowCursor(bShow);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain9** pSwapChain)
{
	return m_pDevice->CreateAdditionalSwapChain(pPresentationParameters, pSwapChain);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetSwapChain(UINT iSwapChain, IDirect3DSwapChain9** pSwapChain)
{
	return m_pDevice->GetSwapChain(iSwapChain, pSwapChain);
}

UINT __stdcall IDirect3DDevice9ProxyEx::GetNumberOfSwapChains()
{
	return m_pDevice->GetNumberOfSwapChains();
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::Reset(D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	CGraphics::OnLost();

#ifdef DEBUG
	pPresentationParameters->Windowed = 1;
	pPresentationParameters->Flags = NULL;
	pPresentationParameters->FullScreen_RefreshRateInHz = NULL;
	pPresentationParameters->PresentationInterval = NULL;
	LONG_PTR lptrStyle = GetWindowLongPtr(pPresentationParameters->hDeviceWindow,GWL_STYLE);
	SetWindowLongPtr(pPresentationParameters->hDeviceWindow,GWL_STYLE,lptrStyle | WS_POPUPWINDOW | WS_CAPTION | WS_THICKFRAME);
	SetWindowPos(pPresentationParameters->hDeviceWindow,HWND_NOTOPMOST,0,0,pPresentationParameters->BackBufferWidth,pPresentationParameters->BackBufferHeight,SWP_SHOWWINDOW);
#endif

	HRESULT hr = m_pDevice->Reset(pPresentationParameters);

	if (SUCCEEDED(hr))
	{
		CGraphics::OnReset();
	}
	return hr;
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetBackBuffer(UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9** ppBackBuffer)
{
	return m_pDevice->GetBackBuffer(iSwapChain, iBackBuffer, Type, ppBackBuffer);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetRasterStatus(UINT iSwapChain, D3DRASTER_STATUS* pRasterStatus)
{
	return m_pDevice->GetRasterStatus(iSwapChain, pRasterStatus);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetDialogBoxMode(BOOL bEnableDialogs)
{
	return m_pDevice->SetDialogBoxMode(bEnableDialogs);
}

void __stdcall IDirect3DDevice9ProxyEx::SetGammaRamp(UINT iSwapChain, DWORD Flags, CONST D3DGAMMARAMP* pRamp)
{
	m_pDevice->SetGammaRamp(iSwapChain, Flags, pRamp);
}

void __stdcall IDirect3DDevice9ProxyEx::GetGammaRamp(UINT iSwapChain, D3DGAMMARAMP* pRamp)
{
	m_pDevice->GetGammaRamp(iSwapChain, pRamp);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture, HANDLE* pSharedHandle)
{
	return m_pDevice->CreateTexture(Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::CreateVolumeTexture(UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9** ppVolumeTexture, HANDLE* pSharedHandle)
{
	return m_pDevice->CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture, pSharedHandle);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::CreateCubeTexture(UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppCubeTexture, HANDLE* pSharedHandle)
{
	return m_pDevice->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture, pSharedHandle);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE* pSharedHandle)
{
	return m_pDevice->CreateVertexBuffer(Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9** ppIndexBuffer, HANDLE* pSharedHandle)
{
	return m_pDevice->CreateIndexBuffer(Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::CreateRenderTarget(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
#ifdef DEBUG
	Width = 800;
	Height = 600;
#endif
	return m_pDevice->CreateRenderTarget(Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
	return m_pDevice->CreateDepthStencilSurface(Width, Height, Format, MultiSample, MultisampleQuality, Discard, ppSurface, pSharedHandle);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::UpdateSurface(IDirect3DSurface9* pSourceSurface, CONST RECT* pSourceRect, IDirect3DSurface9* pDestinationSurface, CONST POINT* pDestPoint)
{
	return m_pDevice->UpdateSurface(pSourceSurface, pSourceRect, pDestinationSurface, pDestPoint);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::UpdateTexture(IDirect3DBaseTexture9* pSourceTexture, IDirect3DBaseTexture9* pDestinationTexture)
{
	return m_pDevice->UpdateTexture(pSourceTexture, pDestinationTexture);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetRenderTargetData(IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pDestSurface)
{
	return m_pDevice->GetRenderTargetData(pRenderTarget, pDestSurface);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetFrontBufferData(UINT iSwapChain, IDirect3DSurface9* pDestSurface)
{
	return m_pDevice->GetFrontBufferData(iSwapChain, pDestSurface);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::StretchRect(IDirect3DSurface9* pSourceSurface, CONST RECT* pSourceRect, IDirect3DSurface9* pDestSurface, CONST RECT* pDestRect, D3DTEXTUREFILTERTYPE Filter)
{
	return m_pDevice->StretchRect(pSourceSurface, pSourceRect, pDestSurface, pDestRect, Filter);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::ColorFill(IDirect3DSurface9* pSurface, CONST RECT* pRect, D3DCOLOR color)
{
	return m_pDevice->ColorFill(pSurface, pRect, color);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::CreateOffscreenPlainSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
	return m_pDevice->CreateOffscreenPlainSurface(Width, Height, Format, Pool, ppSurface, pSharedHandle);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9* pRenderTarget)
{
	HRESULT hr =  m_pDevice->SetRenderTarget(RenderTargetIndex, pRenderTarget);
	if(pRenderTarget != NULL)
	{
		// Begin drawing our 3d stuffs (Before truck and ets stuffs)
	} else {
		// End drawing our 3d stuffs (After trucks and ets stuffs)
	}
	return hr;
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9** ppRenderTarget)
{
	return m_pDevice->GetRenderTarget(RenderTargetIndex, ppRenderTarget);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetDepthStencilSurface(IDirect3DSurface9* pNewZStencil)
{
	return m_pDevice->SetDepthStencilSurface(pNewZStencil);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetDepthStencilSurface(IDirect3DSurface9** ppZStencilSurface)
{
	return m_pDevice->GetDepthStencilSurface(ppZStencilSurface);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::BeginScene()
{
	return m_pDevice->BeginScene();
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::EndScene()
{
	CGraphics::Render();
	return m_pDevice->EndScene();
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::Clear(DWORD Count, CONST D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil)
{
	return m_pDevice->Clear(Count, pRects, Flags, Color, Z, Stencil);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetTransform(D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* mat)
{
	return m_pDevice->SetTransform(State, mat);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetTransform(D3DTRANSFORMSTATETYPE State, D3DMATRIX* mat)
{
	return m_pDevice->GetTransform(State, mat);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::MultiplyTransform(D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* mat)
{
	return m_pDevice->MultiplyTransform(State, mat);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetViewport(CONST D3DVIEWPORT9* pViewport)
{
	return m_pDevice->SetViewport(pViewport);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetViewport(D3DVIEWPORT9* pViewport)
{
	return m_pDevice->GetViewport(pViewport);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetMaterial(CONST D3DMATERIAL9* pMaterial)
{
	return m_pDevice->SetMaterial(pMaterial);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetMaterial(D3DMATERIAL9* pMaterial)
{
	return m_pDevice->GetMaterial(pMaterial);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetLight(DWORD Index, CONST D3DLIGHT9* pLight)
{
	return m_pDevice->SetLight(Index, pLight);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetLight(DWORD Index, D3DLIGHT9* pLight)
{
	return m_pDevice->GetLight(Index, pLight);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::LightEnable(DWORD Index, BOOL Enable)
{
	return m_pDevice->LightEnable(Index, Enable);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetLightEnable(DWORD Index, BOOL* pEnable)
{
	return m_pDevice->GetLightEnable(Index, pEnable);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetClipPlane(DWORD Index, CONST float* pPlane)
{
	return m_pDevice->SetClipPlane(Index, pPlane);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetClipPlane(DWORD Index, float* pPlane)
{
	return m_pDevice->GetClipPlane(Index, pPlane);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)
{
	return m_pDevice->SetRenderState(State, Value);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetRenderState(D3DRENDERSTATETYPE State, DWORD* pValue)
{
	return m_pDevice->GetRenderState(State, pValue);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::CreateStateBlock(D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9** ppSB)
{
	return m_pDevice->CreateStateBlock(Type, ppSB);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::BeginStateBlock()
{
	return m_pDevice->BeginStateBlock();
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::EndStateBlock(IDirect3DStateBlock9** ppSB)
{
	return m_pDevice->EndStateBlock(ppSB);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetClipStatus(CONST D3DCLIPSTATUS9* pClipStatus)
{
	return m_pDevice->SetClipStatus(pClipStatus);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetClipStatus(D3DCLIPSTATUS9* pClipStatus)
{
	return m_pDevice->GetClipStatus(pClipStatus);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetTexture(DWORD Stage, IDirect3DBaseTexture9** ppTexture)
{
	return m_pDevice->GetTexture(Stage, ppTexture);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetTexture(DWORD Stage, IDirect3DBaseTexture9* pTexture)
{
	return m_pDevice->SetTexture(Stage, pTexture);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue)
{
	return m_pDevice->GetTextureStageState(Stage, Type, pValue);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value)
{
	return m_pDevice->SetTextureStageState(Stage, Type, Value);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD* pValue)
{
	return m_pDevice->GetSamplerState(Sampler, Type, pValue);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value)
{
	return m_pDevice->SetSamplerState(Sampler, Type, Value);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::ValidateDevice(DWORD* pNumPasses)
{
	return m_pDevice->ValidateDevice(pNumPasses);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetPaletteEntries(UINT PaletteNumber, CONST PALETTEENTRY* pEntries)
{
	return m_pDevice->SetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetPaletteEntries(UINT PaletteNumber, PALETTEENTRY* pEntries)
{
	return m_pDevice->GetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetCurrentTexturePalette(UINT PaletteNumber)
{
	return m_pDevice->SetCurrentTexturePalette(PaletteNumber);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetCurrentTexturePalette(UINT *PaletteNumber)
{
	return m_pDevice->GetCurrentTexturePalette(PaletteNumber);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetScissorRect(CONST RECT* pRect)
{
	return m_pDevice->SetScissorRect(pRect);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetScissorRect(RECT* pRect)
{
	return m_pDevice->GetScissorRect(pRect);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetSoftwareVertexProcessing(BOOL bSoftware)
{
	return m_pDevice->SetSoftwareVertexProcessing(bSoftware);
}

BOOL __stdcall IDirect3DDevice9ProxyEx::GetSoftwareVertexProcessing()
{
	return m_pDevice->GetSoftwareVertexProcessing();
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetNPatchMode(float nSegments)
{
	return m_pDevice->SetNPatchMode(nSegments);
}

float __stdcall IDirect3DDevice9ProxyEx::GetNPatchMode()
{
	return m_pDevice->GetNPatchMode();
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
	return m_pDevice->DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::DrawIndexedPrimitive(D3DPRIMITIVETYPE Type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{
	return m_pDevice->DrawIndexedPrimitive(Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return m_pDevice->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT PrimitiveCount, CONST void* pIndexData, D3DFORMAT IndexDataFormat, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return m_pDevice->DrawIndexedPrimitiveUP(PrimitiveType, MinVertexIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::ProcessVertices(UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer9* pDestBuffer, IDirect3DVertexDeclaration9* pVertexDecl, DWORD Flags)
{
	return m_pDevice->ProcessVertices(SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::CreateVertexDeclaration(CONST D3DVERTEXELEMENT9* pVertexElements, IDirect3DVertexDeclaration9** ppDecl)
{
	return m_pDevice->CreateVertexDeclaration(pVertexElements, ppDecl);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl)
{
	return m_pDevice->SetVertexDeclaration(pDecl);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetVertexDeclaration(IDirect3DVertexDeclaration9** ppDecl)
{
	return m_pDevice->GetVertexDeclaration(ppDecl);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetFVF(DWORD FVF)
{
	return m_pDevice->SetFVF(FVF);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetFVF(DWORD* pFVF)
{
	return m_pDevice->GetFVF(pFVF);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::CreateVertexShader(CONST DWORD* pFunction, IDirect3DVertexShader9** ppShader)
{
	return m_pDevice->CreateVertexShader(pFunction, ppShader);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetVertexShader(IDirect3DVertexShader9* pShader)
{
	return m_pDevice->SetVertexShader(pShader);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetVertexShader(IDirect3DVertexShader9** ppShader)
{
	return m_pDevice->GetVertexShader(ppShader);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetVertexShaderConstantF(UINT StartRegister, CONST float* pConstantData, UINT Vector4fCount)
{
	return m_pDevice->SetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetVertexShaderConstantF(UINT StartRegister, float* pConstantData, UINT Vector4fCount)
{
	return m_pDevice->GetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetVertexShaderConstantI(UINT StartRegister, CONST int* pConstantData, UINT Vector4iCount)
{
	return m_pDevice->SetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetVertexShaderConstantI(UINT StartRegister, int* pConstantData, UINT Vector4iCount)
{
	return m_pDevice->GetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetVertexShaderConstantB(UINT StartRegister, CONST BOOL* pConstantData, UINT BoolCount)
{
	return m_pDevice->SetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetVertexShaderConstantB(UINT StartRegister, BOOL* pConstantData, UINT BoolCount)
{
	return m_pDevice->GetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData, UINT OffsetInBytes, UINT Stride)
{
	return m_pDevice->SetStreamSource(StreamNumber, pStreamData, OffsetInBytes, Stride);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9** ppStreamData, UINT* OffsetInBytes, UINT* pStride)
{
	return m_pDevice->GetStreamSource(StreamNumber, ppStreamData, OffsetInBytes, pStride);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetStreamSourceFreq(UINT StreamNumber, UINT Divider)
{
	return m_pDevice->SetStreamSourceFreq(StreamNumber, Divider);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetStreamSourceFreq(UINT StreamNumber, UINT* Divider)
{
	return m_pDevice->GetStreamSourceFreq(StreamNumber, Divider);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetIndices(IDirect3DIndexBuffer9* pIndexData)
{
	return m_pDevice->SetIndices(pIndexData);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetIndices(IDirect3DIndexBuffer9** ppIndexData)
{
	return m_pDevice->GetIndices(ppIndexData);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::CreatePixelShader(CONST DWORD* pFunction, IDirect3DPixelShader9** ppShader)
{
	return m_pDevice->CreatePixelShader(pFunction, ppShader);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetPixelShader(IDirect3DPixelShader9* pShader)
{
	return m_pDevice->SetPixelShader(pShader);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetPixelShader(IDirect3DPixelShader9** ppShader)
{
	return m_pDevice->GetPixelShader(ppShader);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetPixelShaderConstantF(UINT StartRegister, CONST float* pConstantData, UINT Vector4fCount)
{
	return m_pDevice->SetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetPixelShaderConstantF(UINT StartRegister, float* pConstantData, UINT Vector4fCount)
{
	return m_pDevice->GetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetPixelShaderConstantI(UINT StartRegister, CONST int* pConstantData, UINT Vector4iCount)
{
	return m_pDevice->SetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetPixelShaderConstantI(UINT StartRegister, int* pConstantData, UINT Vector4iCount)
{
	return m_pDevice->GetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetPixelShaderConstantB(UINT StartRegister, CONST BOOL* pConstantData, UINT BoolCount)
{
	return m_pDevice->SetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetPixelShaderConstantB(UINT StartRegister, BOOL* pConstantData, UINT BoolCount)
{
	return m_pDevice->GetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::DrawRectPatch(UINT Handle, CONST float* pNumSegs, CONST D3DRECTPATCH_INFO* pRectPatchInfo)
{
	return m_pDevice->DrawRectPatch(Handle, pNumSegs, pRectPatchInfo);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::DrawTriPatch(UINT Handle, CONST float* pNumSegs, CONST D3DTRIPATCH_INFO* pTriPatchInfo)
{
	return m_pDevice->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::DeletePatch(UINT Handle)
{
	return m_pDevice->DeletePatch(Handle);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::CreateQuery(D3DQUERYTYPE Type, IDirect3DQuery9** ppQuery)
{
	return m_pDevice->CreateQuery(Type, ppQuery);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetConvolutionMonoKernel(UINT width,UINT height,float* rows,float* columns)
{
	return m_pDevice->SetConvolutionMonoKernel(width,height,rows,columns);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::ComposeRects(IDirect3DSurface9* pSrc,IDirect3DSurface9* pDst,IDirect3DVertexBuffer9* pSrcRectDescs,UINT NumRects,IDirect3DVertexBuffer9* pDstRectDescs,D3DCOMPOSERECTSOP Operation,int Xoffset,int Yoffset)
{
	return m_pDevice->ComposeRects(pSrc,pDst,pSrcRectDescs,NumRects,pDstRectDescs,Operation,Xoffset,Yoffset);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::PresentEx(CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion,DWORD dwFlags)
{
	return m_pDevice->PresentEx(pSourceRect,pDestRect,hDestWindowOverride,pDirtyRegion,dwFlags);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetGPUThreadPriority(INT* pPriority)
{
	return m_pDevice->GetGPUThreadPriority(pPriority);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetGPUThreadPriority(INT Priority)
{
	return m_pDevice->SetGPUThreadPriority(Priority);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::WaitForVBlank(UINT iSwapChain)
{
	return m_pDevice->WaitForVBlank(iSwapChain);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::CheckResourceResidency(IDirect3DResource9** pResourceArray,UINT32 NumResources)
{
	return m_pDevice->CheckResourceResidency(pResourceArray,NumResources);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::SetMaximumFrameLatency(UINT MaxLatency)
{
	return m_pDevice->SetMaximumFrameLatency(MaxLatency);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetMaximumFrameLatency(UINT* pMaxLatency)
{
	return m_pDevice->GetMaximumFrameLatency(pMaxLatency);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::CheckDeviceState(HWND hDestinationWindow)
{
	return m_pDevice->CheckDeviceState(hDestinationWindow);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::CreateRenderTargetEx(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Lockable,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle,DWORD Usage)
{
#ifdef DEBUG
	Width = 800;
	Height = 600;
#endif
	return m_pDevice->CreateRenderTargetEx(Width,Height,Format,MultiSample,MultisampleQuality,Lockable,ppSurface,pSharedHandle,Usage);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::CreateOffscreenPlainSurfaceEx(UINT Width,UINT Height,D3DFORMAT Format,D3DPOOL Pool,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle,DWORD Usage)
{
	return m_pDevice->CreateOffscreenPlainSurfaceEx(Width,Height,Format,Pool,ppSurface,pSharedHandle,Usage);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::CreateDepthStencilSurfaceEx(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Discard,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle,DWORD Usage)
{
	return m_pDevice->CreateDepthStencilSurfaceEx(Width,Height,Format,MultiSample,MultisampleQuality,Discard,ppSurface,pSharedHandle,Usage);
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::ResetEx(D3DPRESENT_PARAMETERS* pPresentationParameters,D3DDISPLAYMODEEX *pFullscreenDisplayMode)
{
	CGraphics::OnReset();

	HRESULT hr = m_pDevice->ResetEx(pPresentationParameters,pFullscreenDisplayMode);

	if (SUCCEEDED(hr))
	{
		CGraphics::OnLost();
	}
	return hr;
}

HRESULT __stdcall IDirect3DDevice9ProxyEx::GetDisplayModeEx(UINT iSwapChain,D3DDISPLAYMODEEX* pMode,D3DDISPLAYROTATION* pRotation)
{
	return m_pDevice->GetDisplayModeEx(iSwapChain,pMode,pRotation);
}

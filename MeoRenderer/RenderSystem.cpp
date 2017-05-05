#include "stdafx.h"
#include "RenderSystem.h"

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")


RenderSystem::RenderSystem()
{
}

RenderSystem::~RenderSystem()
{
}

bool RenderSystem::Initialize( HWND hWnd )
{
	m_hWnd = hWnd;
	assert(m_hWnd);

	bool bOK = InitDeviceAndSwapChain();
	assert(bOK);

	bOK = InitBackBuffer();

	return bOK;
}

void RenderSystem::Shutdown()
{
}

void RenderSystem::Frame()
{
}

bool RenderSystem::InitDeviceAndSwapChain()
{
	HRESULT hr;

	D3D_FEATURE_LEVEL eFeatureLevel = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL eFeatureLevelSupported;
	UINT eCreateDeviceFlag = 0;
#ifdef _DEBUG
	eCreateDeviceFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	DXGI_SWAP_CHAIN_DESC scDesc;
	memset(&scDesc, 0, sizeof(DXGI_SWAP_CHAIN_DESC));
	scDesc.BufferCount = 1;
	scDesc.BufferDesc.Width = 640;
	scDesc.BufferDesc.Height = 480;
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	scDesc.BufferDesc.RefreshRate.Numerator = 60;
	scDesc.BufferDesc.RefreshRate.Denominator = 1;
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scDesc.OutputWindow = m_hWnd;
	scDesc.SampleDesc.Count = 1;
	scDesc.SampleDesc.Quality = 0;
	scDesc.Windowed = TRUE;
	scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	hr = D3D11CreateDeviceAndSwapChain(
		nullptr,                    // Adapter
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,                    // Software
		eCreateDeviceFlag,
		&eFeatureLevel, 1,
		D3D11_SDK_VERSION,
		&scDesc,
		&m_pSwapChain,
		&m_pDevice,
		&eFeatureLevelSupported,
		&m_pContext
	);

	if (FAILED(hr)) return false;

	return true;
}

bool RenderSystem::InitBackBuffer()
{
	HRESULT hr;

	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&m_pBackBuffer);
	if (FAILED(hr)) return false;

	m_pDevice->CreateRenderTargetView(m_pBackBuffer, nullptr, &m_pRenderTarget);
	if (FAILED(hr)) return false;

	D3D11_TEXTURE2D_DESC;
	D3D11_DEPTH_STENCIL_DESC;
	D3D11_DEPTH_STENCIL_VIEW_DESC;
}

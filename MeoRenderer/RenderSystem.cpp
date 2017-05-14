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

bool RenderSystem::Initialize( HWND hWnd, uint32_t uWidth, uint32_t uHeight )
{
	m_hWnd = hWnd;
	assert(m_hWnd);

	m_uWidth = uWidth;
	m_uHeight = uHeight;
	assert(m_uWidth != 0 && m_uHeight != 0);

	bool bOK = InitDeviceAndSwapChain();
	assert(bOK);

	bOK = InitBackBuffer();
	assert(bOK);

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
	scDesc.BufferDesc.Width = m_uWidth;
	scDesc.BufferDesc.Height = m_uHeight;
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

	return true;
}

bool RenderSystem::InitDepthStencilBuffer()
{
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;

	// Initialize the description of the depth buffer.
	std::memset(&depthBufferDesc, 0, sizeof(depthBufferDesc));

	// Set up the description of the depth buffer.
	depthBufferDesc.Width = m_uWidth;
	depthBufferDesc.Height = m_uHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	HRESULT hr = m_pDevice->CreateTexture2D(&depthBufferDesc, nullptr, &m_pDepthStencilBuffer);
	if (FAILED(hr))
	{
		return false;
	}

	// Initialize the description of the stencil state.
	std::memset(&depthStencilDesc, 0, sizeof(depthStencilDesc));

	// Set up the description of the stencil state.
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil front face
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil back face
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create the depth stencil state.
	hr = m_pDevice->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

#include "stdafx.h"
#include "RenderSystem.h"

#include "MeoPipelineStateObject.h"
#include "MeoShader.h"
#include "MeoSimpleMesh.h"

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")


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

	bOK = InitDepthStencilBuffer();
	assert(bOK);

	m_pContext->OMSetRenderTargets(1, &m_pRenderTarget, m_pDepthStencilView);
	
	D3D11_VIEWPORT viewport;
	// Setup the viewport for rendering.
	viewport.Width = (float)m_uWidth;
	viewport.Height = (float)m_uHeight;
	viewport.MinDepth = 0.f;
	viewport.MaxDepth = 1.f;
	viewport.TopLeftX = 0.f;
	viewport.TopLeftY = 0.f;
	m_pContext->RSSetViewports(1, &viewport);

	bOK = InitMainPso();
	assert(bOK);

	m_pMesh = new MeoSimpleMesh;
	m_pMesh->Initialize(m_pDevice);

	return bOK;
}

void RenderSystem::Shutdown()
{
	m_pPso->Release();
	delete m_pPso;

	m_pDepthStencilView->Release();
	m_pDepthStencilBuffer->Release();
	m_pRenderTarget->Release();
	m_pContext->Release();
	m_pDevice->Release();
	m_pSwapChain->Release();
}

void RenderSystem::Update()
{
}

void RenderSystem::Draw()
{
	float clearColor[4];
	clearColor[0] = 0.f;
	clearColor[1] = 0.f;
	clearColor[2] = 0.f;
	clearColor[3] = 1.f;
	m_pContext->ClearRenderTargetView(m_pRenderTarget, clearColor);
	m_pContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	SetPso(m_pPso);

	m_pMesh->Render(m_pContext);

	m_pSwapChain->Present(0, 0);
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
	std::memset(&depthBufferDesc, 0, sizeof(depthBufferDesc));

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

	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	std::memset(&depthStencilViewDesc, 0, sizeof(depthStencilViewDesc));

	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	hr = m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer, &depthStencilViewDesc, &m_pDepthStencilView);
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool RenderSystem::InitMainPso()
{
	m_pPso = new MeoPipelineStateObject( m_pDevice, m_pContext );
	m_pPso->CreateDepthStencilState();
	m_pPso->CreateRasterizerState();
	m_pPso->CreateBlendState();

	MeoShader* pShader = new MeoShader(m_pDevice, m_pContext);
	pShader->CreateVertexShader(L"Shaders/ColorShader.hlsl");
	pShader->CreatePixelShader(L"Shaders/ColorShader.hlsl");

	m_pPso->pShaders = pShader;

	return true;
}

bool RenderSystem::SetPso(MeoPipelineStateObject* pPso)
{
	m_pContext->IASetInputLayout(pPso->pShaders->GetInputLayout());
	m_pContext->VSSetShader(pPso->pShaders->GetVertexShader(), NULL, 0);
	m_pContext->PSSetShader(pPso->pShaders->GetPixelShader(), NULL, 0);
	m_pContext->RSSetState(pPso->pRasterizerState);
	m_pContext->OMSetBlendState(pPso->pBlenderState, 0, 0xffffffff);
	m_pContext->OMSetDepthStencilState(pPso->pDepthStencilState, 0);
	return true;
}

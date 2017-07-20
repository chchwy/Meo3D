#include "stdafx.h"
#include "MeoPipelineStateObject.h"
#include "MeoShader.h"


MeoPipelineStateObject::MeoPipelineStateObject(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	assert(pDevice && pContext);
	m_pDevice = pDevice;
	m_pContext = pContext;
}

MeoPipelineStateObject::~MeoPipelineStateObject()
{
}

void MeoPipelineStateObject::Release()
{
	pDepthStencilState->Release();
	pDepthStencilState = nullptr;

	pRasterizerState->Release();
	pRasterizerState = nullptr;
}

bool MeoPipelineStateObject::CreateDepthStencilState()
{
	// Initialize the description of the stencil state.
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
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
	HRESULT hr = m_pDevice->CreateDepthStencilState(&depthStencilDesc, &pDepthStencilState);
	if (FAILED(hr))
	{
		return false;
	}
	return false;
}

bool MeoPipelineStateObject::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC rasterDesc;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.CullMode = D3D11_CULL_NONE;
	rasterDesc.FrontCounterClockwise = false;

	rasterDesc.DepthBias = 1;
	rasterDesc.DepthBiasClamp = 1.0f;
	rasterDesc.SlopeScaledDepthBias = 1.0f;
	rasterDesc.DepthClipEnable = true;
	
	rasterDesc.ScissorEnable = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.AntialiasedLineEnable = false;

	HRESULT hr = m_pDevice->CreateRasterizerState(&rasterDesc, &pRasterizerState);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

bool MeoPipelineStateObject::CreateBlendState()
{
	D3D11_BLEND_DESC bDesc;
	bDesc.AlphaToCoverageEnable = false;
	bDesc.IndependentBlendEnable = false; // use rendertarget[0] state only

	bDesc.RenderTarget[0].BlendEnable = true;
	bDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	bDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_DEST_ALPHA;
	bDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	HRESULT hr = m_pDevice->CreateBlendState(&bDesc, &pBlenderState);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

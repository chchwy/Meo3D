#include "stdafx.h"
#include "MeoShader.h"

#include <iostream>
#include <d3dcompiler.h>


MeoShader::~MeoShader()
{
	SAFE_RELEASE(m_pVertexShader);
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pCompiledCodeVertex);
	SAFE_RELEASE(m_pCompiledCodePixel);

	m_pDevice = nullptr;
	m_pContext = nullptr;
}

bool MeoShader::CreateVertexShader(std::wstring sFilePath)
{
	ID3DBlob* pErrorMsg = nullptr;

	UINT sCompileFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	sCompileFlags |= D3DCOMPILE_DEBUG;
#endif

	HRESULT hr = D3DCompileFromFile(
		sFilePath.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"vs_main",
		"vs_5_0",
		sCompileFlags,
		0,
		&m_pCompiledCodeVertex,
		&pErrorMsg
	);

	if (FAILED(hr))
	{
		if (pErrorMsg)
		{
			char msg[8192];
			std::memset(msg, 0, 8192);
			std::memcpy(msg, (char*)pErrorMsg->GetBufferPointer(), pErrorMsg->GetBufferSize());
			std::cout << msg;
		}
	}

	hr = m_pDevice->CreateVertexShader(m_pCompiledCodeVertex->GetBufferPointer(), m_pCompiledCodeVertex->GetBufferSize(), nullptr, &m_pVertexShader);

	D3D11_INPUT_ELEMENT_DESC inputLayout[2];
	inputLayout[0].SemanticName = "POSITION";
	inputLayout[0].SemanticIndex = 0;
	inputLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	inputLayout[0].InputSlot = 0;
	inputLayout[0].AlignedByteOffset = 0;
	inputLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	inputLayout[0].InstanceDataStepRate = 0;

	inputLayout[1].SemanticName = "COLOR";
	inputLayout[1].SemanticIndex = 0;
	inputLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	inputLayout[1].InputSlot = 0;
	inputLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	inputLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	inputLayout[1].InstanceDataStepRate = 0;

	hr = m_pDevice->CreateInputLayout(
		inputLayout, 2, 
		m_pCompiledCodeVertex->GetBufferPointer(),
		m_pCompiledCodeVertex->GetBufferSize(),
		&m_pInputLayout);

	if (FAILED(hr))
	{
		std::cout << "ERROR: Failed to create InputLayout";
	}
	return true;
}

bool MeoShader::CreatePixelShader(std::wstring sFilePath)
{
	ID3DBlob* pErrorMsg = nullptr;

	UINT sCompileFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	sCompileFlags |= D3DCOMPILE_DEBUG;
#endif

	HRESULT hr = D3DCompileFromFile(
		sFilePath.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"ps_main",
		"ps_5_0",
		sCompileFlags,
		0,
		&m_pCompiledCodePixel,
		&pErrorMsg
	);

	if (FAILED(hr))
	{
		if (pErrorMsg)
		{
			char msg[8192];
			std::memset(msg, 0, 8192);
			std::memcpy(msg, (char*)pErrorMsg->GetBufferPointer(), pErrorMsg->GetBufferSize());
			std::cout << msg;
		}
	}

	hr = m_pDevice->CreatePixelShader(m_pCompiledCodePixel->GetBufferPointer(), m_pCompiledCodePixel->GetBufferSize(), nullptr, &m_pPixelShader);
	return true;
}

std::wstring MeoShader::GetError()
{
	return L"";
}

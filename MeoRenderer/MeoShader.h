#pragma once

#include <string>


class MeoShader
{
public:
	MeoShader(ID3D11Device* pDevice, ID3D11DeviceContext* pContext) { m_pDevice = pDevice; m_pContext = pContext; }
	~MeoShader();

	bool CreateVertexShader(std::wstring sFilePath);
	bool CreatePixelShader(std::wstring sFilePath);

	std::wstring GetError();

	ID3D11InputLayout* GetInputLayout() { return m_pInputLayout; }
	ID3D11VertexShader* GetVertexShader() { return m_pVertexShader; }
	ID3D11PixelShader* GetPixelShader() { return m_pPixelShader; }

private:
	ID3DBlob* m_pCompiledCodeVertex = nullptr;
	ID3DBlob* m_pCompiledCodePixel  = nullptr;
	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3D11PixelShader* m_pPixelShader = nullptr;
	ID3D11InputLayout* m_pInputLayout = nullptr;

	ID3D11Device* m_pDevice = nullptr;
	ID3D11DeviceContext* m_pContext = nullptr;
};


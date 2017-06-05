#pragma once

#include <string>

class MeoShader;


class MeoPipelineStateObject
{
public:
	MeoPipelineStateObject( ID3D11Device* pDevice, ID3D11DeviceContext* pContext );
	~MeoPipelineStateObject();

	void Release();

	bool CreateDepthStencilState();
	bool CreateRasterizerState();

	ID3D11DepthStencilState* pDepthStencilState = nullptr;
	ID3D11RasterizerState* pRasterizerState = nullptr;

	MeoShader* pShaders = nullptr;

private:
	ID3D11Device* m_pDevice = nullptr;
	ID3D11DeviceContext* m_pContext = nullptr;
};


#pragma once
class MeoPipelineStateObject
{
public:
	MeoPipelineStateObject( ID3D11Device* pDevice, ID3D11DeviceContext* pContext );
	~MeoPipelineStateObject();

	bool CreateDepthStencilState();
	bool CreateRasterizerState();

	ID3D11DepthStencilState* pDepthStencilState = nullptr;
	ID3D11RasterizerState* pRasterizerState = nullptr;

private:
	ID3D11Device* m_pDevice = nullptr;
	ID3D11DeviceContext* m_pContext = nullptr;
};


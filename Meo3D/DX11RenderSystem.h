#pragma once

#include "stdafx.h"


class MeoPipelineStateObject;
class MeoScene;
class MeoSimpleMesh;


class DX11RenderSystem
{
public:
	DX11RenderSystem();
	~DX11RenderSystem();

	bool Initialize(HWND hWnd, uint32_t uWidth, uint32_t uHeight);
	void Shutdown();

	void Update();
	void Draw();

    ID3D11Device* GetDevice() const { return m_pDevice; }

    void SetScene( std::shared_ptr<MeoScene> spScene );
private:
	// D3D 11 initialization
	bool InitDeviceAndSwapChain();
	bool InitBackBuffer();
	bool InitDepthStencilBuffer();

	bool InitMainPso();
	bool SetPipelineStateObject(MeoPipelineStateObject* pPso);

private:
	HWND m_hWnd = 0;
	uint32_t m_uWidth = 0;
	uint32_t m_uHeight = 0;

	ID3D11Device*        m_pDevice = nullptr;
	ID3D11DeviceContext* m_pContext = nullptr;
	IDXGISwapChain*      m_pSwapChain = nullptr;

	ID3D11Texture2D* m_pBackBuffer = nullptr;
	ID3D11RenderTargetView* m_pRenderTarget = nullptr;

	ID3D11Texture2D* m_pDepthStencilBuffer = nullptr;
	ID3D11DepthStencilView* m_pDepthStencilView = nullptr;

	D3D11_VIEWPORT m_viewPort;

	MeoPipelineStateObject* m_pPso = nullptr;

    std::shared_ptr<MeoScene> m_spScene;
};


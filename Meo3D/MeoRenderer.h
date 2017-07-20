#pragma once

#include <memory>

class DX11RenderSystem;


class MeoRenderer
{
public:
	MeoRenderer();
	~MeoRenderer();

	void Initialize(HWND hWnd);
	void Shutdown();
    void Render();

private:
	HWND m_hWnd = 0;
	std::unique_ptr< DX11RenderSystem > m_spRenderSystem;
};
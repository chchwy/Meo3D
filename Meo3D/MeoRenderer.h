#pragma once

#include "resource.h"
#include <memory>

class RenderSystem;


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
	std::unique_ptr< RenderSystem > m_spRenderSystem;
};
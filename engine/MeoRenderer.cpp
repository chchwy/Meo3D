

#include "MeoRenderer.h"

#include <cassert>
#include "dx12/DX12Renderer.h"


MeoRenderer::MeoRenderer()
{
}

MeoRenderer::~MeoRenderer()
{
}

void MeoRenderer::init(HWND hWnd, int width, int height)
{
    m_hWnd = hWnd;

    mNativeRenderer = std::make_unique<DX12Renderer>();
    mNativeRenderer->Init(hWnd, width, height);
}

void MeoRenderer::Shutdown()
{
}

void MeoRenderer::Render()
{
}

void MeoRenderer::Resize(int width, int height)
{
    mNativeRenderer->Resize(width, height);
}



#include "MeoRenderer.h"

#include <cassert>
#include "dx12/DX12Renderer.h"

//#include "MeoScene.h"
//#include "DX11RenderSystem.h"

/*
Vector2U GetWindowSize(HWND hWnd)
{
    RECT rect;
    if (GetWindowRect(hWnd, &rect))
    {
        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;
        return Vector2U(width, height);
    }
    assert( false );
    return Vector2U(0, 0);
}*/

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

    /*
    Vector2U screenSize = GetWindowSize(hWnd);
    m_spRenderSystem = std::make_unique<DX11RenderSystem>();
    m_spRenderSystem->Initialize( m_hWnd, screenSize.x, screenSize.y );

    m_spScene = std::make_unique<MeoScene>( m_spRenderSystem->GetDevice() );
    */
}

void MeoRenderer::Shutdown()
{
    //m_spRenderSystem->Shutdown();
}

void MeoRenderer::Render()
{
    /*
    m_spRenderSystem->SetScene( m_spScene );
    m_spRenderSystem->Update();
    m_spRenderSystem->Draw();
    */
}

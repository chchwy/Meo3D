
#include "stdafx.h"
#include "MeoRenderer.h"

#include <cassert>
#include "MeoMath.h"
#include "RenderSystem.h"


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
}


MeoRenderer::MeoRenderer()
{
}

MeoRenderer::~MeoRenderer()
{
}

void MeoRenderer::Initialize(HWND hWnd)
{
	m_hWnd = hWnd;

	Vector2U screenSize = GetWindowSize(hWnd);
	m_spRenderSystem = std::make_unique<RenderSystem>();
	m_spRenderSystem->Initialize( m_hWnd, screenSize.x, screenSize.y );
}

void MeoRenderer::Shutdown()
{
	m_spRenderSystem->Shutdown();
}

void MeoRenderer::UpdateScene()
{
	m_spRenderSystem->Update();
}

void MeoRenderer::DrawScene()
{
	m_spRenderSystem->Draw();
}


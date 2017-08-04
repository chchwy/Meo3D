#pragma once

#include <memory>

class MeoScene;
class DX11RenderSystem;


class MeoRenderer
{
public:
	MeoRenderer();
	~MeoRenderer();

	void Initialize(HWND hWnd);
	void Shutdown();
    void Render();

    MeoScene* Scene() const { return m_spScene.get(); }

private:
	HWND m_hWnd = 0;
	std::unique_ptr<DX11RenderSystem> m_spRenderSystem;
    std::shared_ptr<MeoScene> m_spScene;
};
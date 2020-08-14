#pragma once

#include <memory>

class MeoScene;
class DX12Renderer;


class MeoRenderer
{
public:
	MeoRenderer();
	~MeoRenderer();

	void init(HWND hWnd, int width, int height);
	void Shutdown();
    void Render();

    //MeoScene* Scene() const { return m_spScene.get(); }

private:
	HWND m_hWnd = 0;
    std::unique_ptr<DX12Renderer> mNativeRenderer;
    //std::shared_ptr<MeoScene> m_spScene;
};

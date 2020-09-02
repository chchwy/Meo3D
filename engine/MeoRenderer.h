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
    void Resize(int width, int height);

private:
	HWND m_hWnd = 0;
    std::unique_ptr<DX12Renderer> mNativeRenderer;
};

#include "meoengine.h"

#include <iostream>
#include "MeoRenderer.h"

MeoEngine::MeoEngine()
{
    //std::cout << "Engine!" << std::endl;
}

void MeoEngine::init(HWND hWnd, int width, int height)
{
    mRenderer = std::make_unique<MeoRenderer>();
    mRenderer->init(hWnd, width, height);
}

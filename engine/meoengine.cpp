#include "meoengine.h"

#include <iostream>
#include "MeoRenderer.h"

MeoEngine::MeoEngine()
{
    //std::cout << "Engine!" << std::endl;
}

void MeoEngine::init(HWND hWnd)
{
    mRenderer = std::make_unique<MeoRenderer>();
    mRenderer->Initialize(hWnd);
}

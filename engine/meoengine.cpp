#include "meoengine.h"

#include <iostream>
#include "MeoRenderer.h"

MeoEngine::MeoEngine()
{
}

void MeoEngine::Init(HWND hWnd, int width, int height)
{
    mRenderer = std::make_unique<MeoRenderer>();
    mRenderer->init(hWnd, width, height);
    mInitialized = true;
}

void MeoEngine::Resize(int width, int height)
{
    if (mInitialized)
        mRenderer->Resize(width, height);
}

void MeoEngine::Draw()
{
    if (mInitialized)
        mRenderer->Draw();
}

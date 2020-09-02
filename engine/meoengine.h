#pragma once

class MeoRenderer;


class MeoEngine
{
public:
    MeoEngine();

    void Init(HWND, int width, int height);
    void Resize(int width, int height);
    void Draw();

private:
    std::unique_ptr<MeoRenderer> mRenderer;

    bool mInitialized = false;
};

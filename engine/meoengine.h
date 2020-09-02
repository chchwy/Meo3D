#pragma once

class MeoRenderer;


class MeoEngine
{
public:
    MeoEngine();

    void Init(HWND, int width, int height);
    void Resize(int width, int height);

private:
    std::unique_ptr<MeoRenderer> mRenderer;
};

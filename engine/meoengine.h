#pragma once

class MeoRenderer;


class MeoEngine
{
public:
    MeoEngine();

    void init(HWND, int width, int height);

private:
    std::unique_ptr<MeoRenderer> mRenderer;
};

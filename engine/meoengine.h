#pragma once

class MeoRenderer;


class MeoEngine
{
public:
    MeoEngine();

    void init(HWND);

private:
    std::unique_ptr<MeoRenderer> mRenderer;
};

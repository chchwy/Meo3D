#pragma once

struct ID3D12Device;

class DX12Renderer
{
public:
    DX12Renderer();
    ~DX12Renderer();

    Status init(HWND, int width, int height);

private:
    HRESULT initD3D(HWND hWnd, int width, int height);
    HRESULT CreateCommandObjects(ID3D12Device*);
    void CreateSwapChain(ID3D12Device*, HWND hWnd, int width, int height);

    ID3D12Device* mDevice;
    ID3D12CommandQueue* mCommandQueue;
    IDXGIFactory* mDxgiFactory;

    int mWidth = 0;
    int mHeight = 0;
    int mMSAAQuality = 0;
};

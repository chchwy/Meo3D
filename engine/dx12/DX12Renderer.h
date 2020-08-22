#pragma once

struct ID3D12Device;

class DX12Renderer
{
public:
    DX12Renderer();
    ~DX12Renderer();

    Status init(HWND, int width, int height);

private:
    Status initD3D(HWND hWnd, int width, int height);
    void CreateCommandObjects(ID3D12Device*);
    void CreateSwapChain(ID3D12Device*, HWND hWnd, int width, int height);
    void CreateDescriptorHeaps(ID3D12Device*);
    void CreateBackBufferRenderTargets();

    IDXGIFactory* mDxgiFactory;
    ID3D12Device* mDevice;
    ID3D12Fence* mFence;
    ID3D12CommandQueue* mCommandQueue;
    ID3D12CommandList* mCommandList;
    ID3D12CommandAllocator* mCommandAllocator;
    IDXGISwapChain* mSwapChain;

    ID3D12DescriptorHeap* mRtvHeap;
    ID3D12DescriptorHeap* mDsvHeap;

    ID3D12Resource* mSwapChainBuffers[2];

    int mWidth = 0;
    int mHeight = 0;
    int mMSAAQuality = 0;

    UINT mRtvDescSize = 0;
};

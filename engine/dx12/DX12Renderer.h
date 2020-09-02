#pragma once

using Microsoft::WRL::ComPtr;
struct ID3D12Device;

class DX12Renderer
{
public:
    DX12Renderer();
    ~DX12Renderer();

    Status Init(HWND, int width, int height);
    Status Resize(int width, int height);

    int GetWidth() { return mWidth; }
    int GetHeight() { return mHeight; }

private:
    Status InitD3D(HWND hWnd, int width, int height);
    Status InitD3DCatchException(HWND hWnd, int width, int height);

    void CreateCommandObjects(ID3D12Device*);
    void CreateSwapChain(HWND hWnd, int width, int height);
    void CreateDescriptorHeaps(ID3D12Device*);
    void CreateBackBufferRenderTargets();
    void CreateDepthStencilBuffer();

    void FlushCommandQueue();

    ComPtr<IDXGIFactory> mDxgiFactory;
    ComPtr<ID3D12Device> mDevice;
    ComPtr<ID3D12Fence> mFence;
    ComPtr<ID3D12CommandQueue> mCommandQueue;
    ComPtr<ID3D12GraphicsCommandList> mCommandList;
    ComPtr<ID3D12CommandAllocator> mCommandAllocator;
    ComPtr<IDXGISwapChain> mSwapChain;

    ComPtr<ID3D12DescriptorHeap> mRtvHeap;
    ComPtr<ID3D12DescriptorHeap> mDsvHeap;

    ComPtr<ID3D12Resource> mSwapChainBuffers[2];
    ComPtr<ID3D12Resource> mDepthStencilBuffer;

    D3D12_VIEWPORT mViewport;
    D3D12_RECT mScissorRect;

    int mWidth = 0;
    int mHeight = 0;
    int mMSAAQuality = 0;

    UINT mRtvDescSize = 0;
    UINT mDsvDescSize = 0;
    UINT mCbvSrvUavDescSize = 0;

    UINT mCurrentFence = 0;
};

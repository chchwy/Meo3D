#include "DX12Renderer.h"
#include <iostream>
#include <system_error>
#include <cassert>
#include "d3dx12.h"

#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")


#define BACK_BUFFER_FORMAT DXGI_FORMAT_R8G8B8A8_UNORM

DX12Renderer::DX12Renderer()
{
}

DX12Renderer::~DX12Renderer()
{
    mDxgiFactory->Release();
    mDevice->Release();
    mFence->Release();
    mCommandQueue->Release();
    mCommandList->Release();
    mCommandAllocator->Release();
    mSwapChain->Release();

    mSwapChainBuffers[0]->Release();
    mSwapChainBuffers[1]->Release();
}

Status DX12Renderer::init(HWND hWnd, int width, int height)
{
    debugLog("Init Dx12 Renderer!");

    mWidth = width;
    mHeight = height;
    //try
    //{
        initD3D(hWnd, width, height);
    //}
    //catch (const std::exception&)
    //{
    //    assert(false);
    //    return Status::FAIL;
    //}
    return Status::OK;
}


Status DX12Renderer::initD3D(HWND hWnd, int width, int height)
{

#ifdef ENABLE_DEBUG_LAYER
    ID3D12Debug* debugController;
    D3D12GetDebugInterface(IID_PPV_ARGS(&debugController));
    debugController->EnableDebugLayer();
#endif

    IDXGIFactory4* dxgiFactory;
    HRESULT hr = CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory));
    if (FAILED(hr))
    {
        return Status::FAIL;
    }

    ID3D12Device* device;
    hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device));

    ID3D12Fence* fence;
    hr = device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));

    mDxgiFactory = dxgiFactory;
    mDevice = device;
    mFence = fence;

    mRtvDescSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    UINT dsvDescSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
    UINT cbvSrvUavDescSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

    D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS msaaQualityLevels;
    msaaQualityLevels.Format = BACK_BUFFER_FORMAT;
    msaaQualityLevels.SampleCount = 4;
    msaaQualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
    msaaQualityLevels.NumQualityLevels = 0;
    device->CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &msaaQualityLevels, sizeof(msaaQualityLevels));

    mMSAAQuality = msaaQualityLevels.NumQualityLevels;
    debugLog(std::string("MSAA Quality=") + std::to_string(mMSAAQuality));
    assert(mMSAAQuality > 0 && "Unexpected MSAA quality level.");

    CreateCommandObjects(device);
    CreateSwapChain(device, hWnd, width, height);
    CreateDescriptorHeaps(device);
    CreateBackBufferRenderTargets();
    CreateDepthStencilBuffer();
    return Status::OK;
}

void DX12Renderer::CreateCommandObjects(ID3D12Device* device)
{
    ID3D12CommandQueue* commandQueue;
    ID3D12CommandAllocator* commandAllocator;
    ID3D12GraphicsCommandList* commandList;

    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    HR(device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&commandQueue)));
    HR(device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator)));
    HR(device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator, nullptr, IID_PPV_ARGS(&commandList)));

    mCommandQueue = commandQueue;
    mCommandList = commandList;
    mCommandAllocator = commandAllocator;

    // Start off in a closed state.
    // This is because the first time we refer to the command list we will Reset it
    // and it needs to be closed before calling Reset
    commandList->Close();
}

void DX12Renderer::CreateSwapChain(ID3D12Device* device, HWND hWnd, int width, int height)
{
    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferDesc.Format = BACK_BUFFER_FORMAT;
    sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = mMSAAQuality - 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferCount = 2;
    sd.OutputWindow = hWnd;
    sd.Windowed = true;
    sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    IDXGISwapChain* swapChain;
    HR(mDxgiFactory->CreateSwapChain(mCommandQueue, &sd, &swapChain));

    mSwapChain = swapChain;
}

void DX12Renderer::CreateDescriptorHeaps(ID3D12Device* device)
{
    D3D12_DESCRIPTOR_HEAP_DESC rtvDesc;
    rtvDesc.NumDescriptors = 2;
    rtvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    rtvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    rtvDesc.NodeMask = 0;
    HR(device->CreateDescriptorHeap(&rtvDesc, IID_PPV_ARGS(&mRtvHeap)));

    D3D12_DESCRIPTOR_HEAP_DESC dsvDesc;
    dsvDesc.NumDescriptors = 1;
    dsvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
    dsvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    dsvDesc.NodeMask = 0;
    HR(device->CreateDescriptorHeap(&dsvDesc, IID_PPV_ARGS(&mDsvHeap)));
}

void DX12Renderer::CreateBackBufferRenderTargets()
{
    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle(mRtvHeap->GetCPUDescriptorHandleForHeapStart());
    for (int i = 0; i < 2; ++i)
    {
        HR(mSwapChain->GetBuffer(i, IID_PPV_ARGS(&mSwapChainBuffers[i])));

        mDevice->CreateRenderTargetView(mSwapChainBuffers[i], nullptr, rtvHeapHandle);
        rtvHeapHandle.Offset(1, mRtvDescSize);
    }
}

void DX12Renderer::CreateDepthStencilBuffer()
{
    D3D12_RESOURCE_DESC d;
    d.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    d.Alignment = 0;
    d.Width = mWidth;
    d.Height = mHeight;
    d.DepthOrArraySize = 1;
    d.MipLevels = 1;
    d.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    d.SampleDesc.Count = 1;
    d.SampleDesc.Quality = mMSAAQuality - 1;
    d.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
    d.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

    D3D12_CLEAR_VALUE c;
    c.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    c.DepthStencil.Depth = 1.0f;
    c.DepthStencil.Stencil = 0;

    CD3DX12_HEAP_PROPERTIES heapProp(D3D12_HEAP_TYPE_DEFAULT);
    HR(mDevice->CreateCommittedResource(&heapProp, D3D12_HEAP_FLAG_NONE,
                                        &d, D3D12_RESOURCE_STATE_COMMON, &c,
                                        IID_PPV_ARGS(&mDepthStencilBuffer)));

    D3D12_CPU_DESCRIPTOR_HANDLE handle = mDsvHeap->GetCPUDescriptorHandleForHeapStart();
    mDevice->CreateDepthStencilView(mDepthStencilBuffer, nullptr, handle); // nullptr only works when the buffer is not typeless


    mCommandList->Reset(mCommandAllocator, nullptr);

    CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(mDepthStencilBuffer, D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_DEPTH_WRITE);
    mCommandList->ResourceBarrier(1, &barrier);

    mCommandList->Close();

    ID3D12CommandList* cmdLists[] = { mCommandList };
    mCommandQueue->ExecuteCommandLists(1, cmdLists);

    FlushCommandQueue();

    mViewport.TopLeftX = 0;
    mViewport.TopLeftY = 0;
    mViewport.Width = mWidth;
    mViewport.Height = mHeight;
    mViewport.MinDepth = 0.0f;
    mViewport.MaxDepth = 1.0f;

    mScissorRect = { 0, 0, mWidth, mHeight };
}

void DX12Renderer::FlushCommandQueue()
{
    mCurrentFence += 1;

    // Add an instruction to the command queue to set a new fence point.  Because we
    // are on the GPU timeline, the new fence point won't be set until the GPU finishes
    // processing all the commands prior to this Signal().
    HR(mCommandQueue->Signal(mFence, mCurrentFence));

    if (mFence->GetCompletedValue() < mCurrentFence)
    {
        HANDLE eventHandle = CreateEventEx(nullptr, false, false, EVENT_ALL_ACCESS);

        mFence->SetEventOnCompletion(mCurrentFence, eventHandle);

        WaitForSingleObject(eventHandle, INFINITE);
        CloseHandle(eventHandle);
    }
}

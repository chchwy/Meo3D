#include "DX12Renderer.h"
#include <iostream>
#include <system_error>
#include <cassert>

#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")


#define BACK_BUFFER_FORMAT DXGI_FORMAT_R8G8B8A8_UNORM

DX12Renderer::DX12Renderer()
{
}

DX12Renderer::~DX12Renderer()
{
}

Status DX12Renderer::init(HWND hWnd, int width, int height)
{
    std::cout << "Init Dx12 Renderer!" << std::endl;

    HRESULT hr = initD3D(hWnd, width, height);
    if (FAILED(hr))
    {
        std::cerr << std::system_category().message(hr);
        return Status::FAIL;
    }

    return Status::OK;
}


HRESULT DX12Renderer::initD3D(HWND hWnd, int width, int height)
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

    mDxgiFactory = dxgiFactory;

    ID3D12Device* device;
    hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device));

    mDevice = device;

    ID3D12Fence* fence;
    hr = device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));

    UINT rtvDescSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    UINT dsvDescSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
    UINT cbvSrvUavDescSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

    D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS msaaQualityLevels;
    msaaQualityLevels.Format = BACK_BUFFER_FORMAT;
    msaaQualityLevels.SampleCount = 4;
    msaaQualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
    msaaQualityLevels.NumQualityLevels = 0;
    device->CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &msaaQualityLevels, sizeof(msaaQualityLevels));

    UINT msaa4xQuality = msaaQualityLevels.NumQualityLevels;
    assert(msaa4xQuality > 0 && "Unexpected MSAA quality level.");

    CreateCommandObjects(device);
    CreateSwapChain(device, hWnd, width, height);

    return hr;
}

HRESULT DX12Renderer::CreateCommandObjects(ID3D12Device* device)
{
    ID3D12CommandQueue* commandQueue;
    ID3D12CommandAllocator* commandAllocator;
    ID3D12GraphicsCommandList* commandList;

    HRESULT hr = S_OK;

    __FUNCTION__;
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    HR(device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&commandQueue)));
    HR(device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator)));
    HR(device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator, nullptr, IID_PPV_ARGS(&commandList)));

    mCommandQueue = commandQueue;

    commandList->Close();
    return hr;
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
    sd.SampleDesc.Quality = 0;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferCount = 2;
    sd.OutputWindow = hWnd;
    sd.Windowed = true;
    sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    IDXGISwapChain* swapChain;
    HR(mDxgiFactory->CreateSwapChain(mCommandQueue, &sd, &swapChain));
}

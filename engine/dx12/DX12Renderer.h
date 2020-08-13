#pragma once


class DX12Renderer
{
public:
    DX12Renderer();
    ~DX12Renderer();

    Status init();

private:
    HRESULT initD3D();
    HRESULT CreateCommandObjects();
    std::unique_ptr<ID3D12Device2> mDevice;
};

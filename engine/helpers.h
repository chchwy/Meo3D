#pragma once

// From DXSampleHelper.h
// Source: https://github.com/Microsoft/DirectX-Graphics-Samples
inline void TF(HRESULT hr)
{
    if (FAILED(hr))
    {
        throw std::exception();
    }
}

class Status
{
public:
    enum ErrorCode
    {
        OK,
        FAIL,
    };

    ErrorCode code;

    Status(ErrorCode c) { code = c; }
};
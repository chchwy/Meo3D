#pragma once

// From DXSampleHelper.h
// Source: https://github.com/Microsoft/DirectX-Graphics-Samples
#define HR(h) ThrowIfFailed((h), __FILE__, __LINE__, __FUNCTION__);

std::string exceptionMessage(HRESULT hr, const char* file, const int line, const char* func);

inline void ThrowIfFailed(HRESULT hr, const char* file, const int line, const char* func)
{
    if (FAILED(hr))
    {
        std::string message = exceptionMessage(hr, file, line, func);
        throw std::exception(message.c_str());
    }
}

void debugLog(std::string s);

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
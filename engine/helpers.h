#pragma once

// From DXSampleHelper.h
// Source: https://github.com/Microsoft/DirectX-Graphics-Samples
#define HR(h) ThrowIfFailed((h), __FILE__, __LINE__, __FUNCTION__);

inline void ThrowIfFailed(HRESULT hr, const char* file, const int line, const char* func)
{
    if (FAILED(hr))
    {
        std::string message = std::system_category().message(hr);
        message += file;
        message += ", LINE ";
        message += std::to_string(line);
        message += "FUNCTION: ";
        message += func;
        std::cout << message;
        //throw std::exception(message.c_str());
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
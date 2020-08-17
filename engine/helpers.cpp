#include "helpers.h"

#include <system_error>
#include <sstream>


std::string exceptionMessage(HRESULT hr, const char* file, const int line, const char* func)
{
    std::string message = std::system_category().message(hr);

    std::stringstream sout;
    sout << "==========================================\n";
    sout << "[HRESULT] " << std::hex << hr << std::endl;
    sout << "[FILE] " << file << std::endl;
    sout << "[LINE] " << line << std::endl;
    sout << "[FUNC] " << func << std::endl;
    sout << "[ERROR] " << message << std::endl;
    sout << "==========================================\n";
    std::string s = sout.str();

    OutputDebugStringA(s.c_str());
    return s;
}

void debugLog(const std::string& s)
{
    std::stringstream sout;
    sout << "[LOG] " << s << "\n";
    OutputDebugStringA(sout.str().c_str());
}

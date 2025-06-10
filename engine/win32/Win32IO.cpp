#include "Win32Utils.hpp"

#include <platform/general_api/IO.hpp>
#include <types/Logger.hpp>


namespace Ruby::Platform {
    void writeInConsole(std::string_view msg, bool isFlush) {
        HANDLE hnd = Win32::getStdHandle(STD_OUTPUT_HANDLE, true);
        DWORD written;
        WriteConsoleA(hnd, msg.data(), static_cast<DWORD>(msg.size()), &written, nullptr);
        
        if (isFlush) {
            FlushFileBuffers(GetStdHandle(STD_OUTPUT_HANDLE));
        }
    }
}
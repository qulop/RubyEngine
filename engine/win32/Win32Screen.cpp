#include "Win32Utils.hpp"

#include <platform/general_api/Screen.hpp>


namespace Ruby::Platform {
    std::pair<i32, i32> getScreenResolution() noexcept {
        i32 width = GetSystemMetrics(SM_CXSCREEN);
        i32 height = GetSystemMetrics(SM_CYSCREEN);

        return std::make_pair(width, height);
    }


    void errorBox(std::string_view msg, std::string_view title) noexcept {
        MessageBoxA(nullptr, msg.data(), title.data(), MB_OK | MB_ICONWARNING | MB_SETFOREGROUND);
    }

    void infoBox(std::string_view msg, std::string_view title) noexcept {
        MessageBoxA(nullptr, msg.data(), title.data(), MB_OK | MB_ICONINFORMATION | MB_SETFOREGROUND);
    }
}
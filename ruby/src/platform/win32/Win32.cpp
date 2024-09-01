#pragma once

#include "Win32.hpp"

#include <utility/Assert.hpp>


namespace Ruby::Platform {
    std::pair<i32, i32> getScreenResolution() noexcept {
        i32 width = GetSystemMetrics(SM_CXSCREEN);
        i32 height = GetSystemMetrics(SM_CYSCREEN);

        return std::make_pair(width, height);
    }

    void errorBox(const char* msg, const char* title) noexcept {
        MessageBox(nullptr, msg, title, MB_OK | MB_ICONWARNING | MB_SETFOREGROUND);
    }

    void infoBox(const char* msg, const char* title) noexcept {
        MessageBox(nullptr, msg, title, MB_OK | MB_ICONINFORMATION | MB_SETFOREGROUND);
    }

    void* virtualAlloc(void* address, size_t len, size_t alignment) {
        RUBY_NOT_IMPLEMENTED;

        return nullptr;
    }
}

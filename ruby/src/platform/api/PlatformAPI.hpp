#pragma once

#include <types/StdInc.hpp>
#include <utility/Definitions.hpp>


namespace Ruby::Platform {
    // Will return X as first and Y as second
    std::pair<i32, i32> getScreenResolution() noexcept;

    void errorBox(const char* msg, const char* title) noexcept;
    void infoBox(const char* msg, const char* title) noexcept;

    void* virtualAlloc(void* address, size_t len, size_t alignment);
    void virtualFree(void* address, size_t len=0);
}
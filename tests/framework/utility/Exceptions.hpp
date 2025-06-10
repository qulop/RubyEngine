#pragma once

#include <types/TypeTraits.hpp>


namespace Ruby::Testify {
    class AssertionError : public std::runtime_error {
        using Super = std::runtime_error;

    public:
        explicit AssertionError(const char* msg) noexcept :
            Super(msg)
        {}
    };


    class SegfaultError : public std::runtime_error {
        using Super = std::runtime_error;

    public:
        SegfaultError() noexcept :
            Super("Segmentation Fault was occurred.")
        {}
    };

    class AbortCalledError : public std::runtime_error {
        using Super = std::runtime_error;
        
    public:
        explicit AbortCalledError(const char* msg) noexcept :
            Super(msg)
        {}
    };
}
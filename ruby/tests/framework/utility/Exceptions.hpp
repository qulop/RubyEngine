#pragma once

#include <types/TypeTraits.hpp>
#include <exception>


namespace Ruby::Testify {
    class AssertionError : public std::exception {
        using Super = std::exception;
    public:
        AssertionError(const char* msg) noexcept :
            Super(msg)
        {}
    };
}
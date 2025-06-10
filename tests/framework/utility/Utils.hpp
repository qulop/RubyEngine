#pragma once

#include "Exceptions.hpp"


namespace Ruby::Testify {
    template<typename ExceptionType=AssertionError>
    void throwIfFalse(bool expr, const char* msg) {
        if (!expr)
            ExceptionType{ msg };
    }
}
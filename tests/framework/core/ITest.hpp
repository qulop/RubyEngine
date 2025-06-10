#pragma once

#include <utility/Definitions.hpp>


namespace Ruby::Testify {
    RUBY_INTERFACE ITest {

        virtual void Run() = 0;
        RUBY_NODISCARD virtual String GetName() const = 0;

        virtual ~ITest() = default;
    };
}
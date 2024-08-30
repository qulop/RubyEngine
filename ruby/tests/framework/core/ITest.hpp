#pragma once

#include <utility/Definitions.hpp>


namespace Ruby::Testify {
    interface ITest {

        virtual void Run() = 0;
        virtual RubyString GetName() const = 0;

        virtual ~ITest() = default;
    };
}
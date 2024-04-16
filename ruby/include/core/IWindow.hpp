#pragma once

#include "WindowProps.hpp"

namespace Ruby
{
    class IWindow
    {
    public:
        RUBY_NODISCARD virtual bool Update() const = 0;
        virtual void PollEvents() = 0;
        RUBY_NODISCARD virtual SizeStruct GetSizes(bool isReal) const = 0;

        virtual ~IWindow() = default;
    };
}
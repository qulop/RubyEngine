#pragma once

#include "WindowProps.hpp"

namespace Ruby
{
    interface IWindow
    {
    public:
        virtual void ChangePosition(i32 x, i32 y) = 0;
        virtual void Resize(u32 x, u32 y) = 0;
        virtual void ToCenter() = 0;
        virtual void SetIcon(const RubyString& path) = 0;
        virtual void SetTitle(const RubyString& title) = 0;
        virtual void PollEvents() = 0;

        RUBY_NODISCARD virtual bool Update() const = 0;
        RUBY_NODISCARD virtual bool IsWindowClosed() const = 0;

        RUBY_NODISCARD virtual SizeStruct GetSizes(bool isReal) const = 0;


        virtual ~IWindow() = default;
    };
}
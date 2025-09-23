#pragma once

#include <types/TypeTraits.hpp>
#include <utility/Definitions.hpp>


namespace Ruby {
    class RUBY_API IndexBuffer {
    public:
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetData(f32* indices, size_t size) = 0;

        RUBY_NODISCARD virtual size_t GetCount() const = 0;


        virtual ~IndexBuffer() = default;
    };
}
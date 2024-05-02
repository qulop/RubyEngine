#pragma once

#include <utility/Definitions.hpp>


namespace Ruby
{
    class VertexBuffer
    {
    public:
        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void SetData(const void* data, size_t size) = 0;

        Ptr<VertexBuffer> Create(size_t size);
        Ptr<VertexBuffer> Create(float* vertices, size_t size);

        ~VertexBuffer() = default;
    };
}
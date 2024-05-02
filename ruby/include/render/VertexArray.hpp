#pragma once

#include <render/Buffers.hpp>

namespace Ruby
{
    class VertexArray
    {
    public:
        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void SetVBO(const Ptr<VertexBuffer>& vbo) = 0;

        static Ptr<VertexArray> Create();

        ~VertexArray() = default;
    };
}
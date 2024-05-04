#pragma once

#include <render/Buffers.hpp>

namespace Ruby
{
    abstract class VertexArray
    {
    public:
        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void SetVBO(const Ptr<VertexBuffer>& vbo) = 0;

        static Ptr<VertexArray> Create();

        virtual ~VertexArray() = default;
    };
}
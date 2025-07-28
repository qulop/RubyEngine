#pragma once

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"


namespace Ruby {
    class RUBY_API VertexArray {
    public:
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        //virtual void AddVBO(const VertexBuffer& vbo) = 0;
        virtual void SetEBO(const IndexBuffer& ebo) = 0;

        RUBY_NODISCARD virtual const Vector<VertexBuffer>& GetVBO() const = 0;
        RUBY_NODISCARD virtual const IndexBuffer* GetEBO() const = 0;

        virtual ~VertexArray() = default;
    };
}
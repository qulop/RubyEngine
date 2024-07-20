#pragma once

#include "Buffers.hpp"


namespace Ruby
{
    class VertexArray
    {
    public:
        VertexArray();
        explicit VertexArray(const VertexBuffer& vbo);

        void Bind() const;
        void Unbind() const;

        void AddVBO(const VertexBuffer& vbo);
        void SetEBO(const IndexBuffer& ebo);

        RUBY_NODISCARD const RubyVector<VertexBuffer>& GetVBO() const;
        RUBY_NODISCARD IndexBuffer GetEBO() const;

        ~VertexArray();

    private:
        u32 m_id = std::numeric_limits<u32>::max();

        RubyVector<VertexBuffer> m_vertexBuffers;
        IndexBuffer m_ebo;
    };
}
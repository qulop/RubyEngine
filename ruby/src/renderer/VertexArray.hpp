#pragma once

#include "Buffers.hpp"


namespace Ruby
{
    class VertexArray
    {
    public:
        VertexArray();
        // VertexArray(const VertexBuffer& vbo); I don't remember what is it should do😖

        void Bind() const;
        void Unbind() const;

        void SetVBO(const VertexBuffer& vbo);

        ~VertexArray();

    private:
        u32 m_id = std::numeric_limits<u32>::max();
    };
}
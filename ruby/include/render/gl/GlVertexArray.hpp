#pragma once

#include <render/VertexArray.hpp>


namespace Ruby
{
    class GlVertexArray : public VertexArray
    {
    public:
        GlVertexArray();

        void Bind();
        void Unbind();

        void SetVBO(const Ptr<VertexBuffer>& vbo);

    private:
        u32 m_id = std::numeric_limits<u32>::max();
    };

}
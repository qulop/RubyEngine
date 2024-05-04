#pragma once

#include <render/VertexArray.hpp>


namespace Ruby
{
    class GlVertexArray : public VertexArray
    {
    public:
        GlVertexArray();

        void Bind() override;
        void Unbind() override;

        void SetVBO(const Ptr<VertexBuffer>& vbo) override;

        virtual ~GlVertexArray();

    private:
        u32 m_id = std::numeric_limits<u32>::max();
    };

}
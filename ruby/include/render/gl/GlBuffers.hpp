#pragma once

#include <render/Buffers.hpp>


namespace Ruby
{
    class GlVertexBuffer : public VertexBuffer
    {
    public:
        GlVertexBuffer(size_t size);
        GlVertexBuffer(float* vertices, size_t size);

        void Bind() override;
        void Unbind() override;

        void SetData(const void* data, size_t size) override;

    private:
        u32 m_id = std::numeric_limits<u32>::max();
    };
}
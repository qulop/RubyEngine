#include <render/Buffers.hpp>
#include <render/gl/GlBuffers.hpp>

namespace Ruby
{
    Ptr<VertexBuffer> VertexBuffer::Create(size_t size)
    {
        return std::make_shared<GlVertexBuffer>(size);
    }

    Ptr<VertexBuffer> VertexBuffer::Create(float* vertices, size_t size)
    {
        return std::make_shared<GlVertexBuffer>(vertices, size);
    }
}
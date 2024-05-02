#include <render/VertexArray.hpp>
#include <render/gl/GlVertexArray.hpp>

namespace Ruby
{
    Ptr<VertexArray> VertexArray::Create()
    {
        return std::make_shared<GlVertexArray>();
    }
}
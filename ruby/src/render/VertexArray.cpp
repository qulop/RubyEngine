#include <render/VertexArray.hpp>
#include <render/gl/GlVertexArray.hpp>

namespace Ruby
{
    /// TODO: ADD CHECK ON USED API
    Ptr<VertexArray> VertexArray::Create()
    {
        return std::make_shared<GlVertexArray>();
    }
}
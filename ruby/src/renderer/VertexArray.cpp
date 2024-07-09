#include <renderer/VertexArray.hpp>
#include <api/opengl/GlVertexArray.hpp>

namespace Ruby
{
    /// TODO: ADD CHECK ON USED API
    Ptr<VertexArray> VertexArray::Create()
    {
        return std::make_shared<GlVertexArray>();
    }
}
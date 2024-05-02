#include <render/gl/GlVertexArray.hpp>
#include <glad/glad.h>


namespace Ruby
{
    GlVertexArray::GlVertexArray()
    {
        glGenVertexArrays(1, &m_id);
    }

    void GlVertexArray::Bind()
    { glBindVertexArray(m_id); }

    void GlVertexArray::Unbind()
    { glBindVertexArray(0); }

    void GlVertexArray::SetVBO(const Ptr<VertexBuffer>& vbo)
    {

    }
}

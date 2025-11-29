#pragma once

#include <renderer/buffers/VertexBuffer.hpp>
#include <utility/Definitions.hpp>

#include <backends/opengl/basic/TypesGL.hpp>


namespace Ruby::OpenGL {
    class RUBY_API VertexBufferGL : public AVertexBuffer {
    public:
        using Super = AVertexBuffer;

    public:
        VertexBufferGL();
        VertexBufferGL(EBufferType type);

        void SetData(const void* data, size_t size) override;

        void InitEmptyBuffer(EBufferType bufferType) override;
        void ReleaseObject() override;

        ~VertexBufferGL() override;

    private:
        GlID m_id = RUBY_GL_UNDEFINED_ID;
    };
}
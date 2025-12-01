#pragma once

#include <renderer/buffers/VertexBuffer.hpp>
#include <utility/Definitions.hpp>

#include <backends/opengl/basic/TypesGL.hpp>


namespace Kiwi::OpenGL {
    class KIWI_API VertexBufferGL : public AVertexBuffer {
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
        GlID m_id = KIWI_GL_UNDEFINED_ID;
    };
}
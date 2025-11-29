#pragma once

#include <types/TypeTraits.hpp>
#include <utility/Definitions.hpp>

#include <renderer/buffers/ObjectGPU.hpp>



namespace Ruby {
    RUBY_ABSTRACT class AVertexBuffer : public IBufferGPU {
    public:
        void InitEmptyBuffer(EBufferType bufferType) override { m_bufferType = bufferType; }

    public:
        virtual void SetData(const void* data, size_t sz) = 0;

        EBufferType GetBufferType() const { return m_bufferType; }

        ~AVertexBuffer() override = default;

    protected:
        size_t m_vertexCount = 0;
        EBufferType m_bufferType = EBufferType::STATIC_BUFFER;
    };
}

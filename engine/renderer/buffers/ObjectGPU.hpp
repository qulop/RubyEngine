#pragma once

#include <types/TypeTraits.hpp>

#include "utility/Definitions.hpp"


namespace Ruby {
    RUBY_FORWARD_DECLARATIONS(
        class GraphicDevice;
    )


    enum class EBufferType {
        STATIC_BUFFER,
        DYNAMIC_BUFFER
    };

    enum class EBufferClass {
        VERTEX_BUFFER,
        INDEX_BUFFER,
        UNIFORM_BUFFER,
        SHADER_STORAGE_BUFFER
    };


    RUBY_INTERFACE IObjectGPU {
    public:
        virtual ~IObjectGPU() = default;

    protected:
        friend class GraphicDevice;

        // Can be released only by the `GraphicDevice`
        virtual void ReleaseObject() = 0;
    };


    RUBY_INTERFACE IBufferGPU : IObjectGPU {
    public:
        ~IBufferGPU() override = default;

    protected:
        friend class GraphicDevice;

        // Can be created only by the `GraphicDevice`
        virtual void InitEmptyBuffer(EBufferType bufferType) = 0;
    };
}

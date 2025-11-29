#pragma once

#include <utility/Definitions.hpp>

#include <renderer/pipeline/GraphicAPI.hpp>
#include <renderer/buffers/ObjectGPU.hpp>


namespace Ruby {
    RUBY_INTERFACE IGraphicObjectsFactory;

    RUBY_ABSTRACT class ARenderInstance;

    RUBY_ABSTRACT class ARenderPipeline;
    RUBY_ABSTRACT class AVertexBuffer;


    // TODO: Should it manage **global** and **shared** buffers: UBO, SSBO and so on?
    RUBY_ABSTRACT class GraphicDevice {
    public:
        explicit GraphicDevice(SharedPtr<IGraphicObjectsFactory> factoryPtr);

        RUBY_NODISCARD EGraphicAPI GetCurrentSelectedAPI();

        RUBY_NODISCARD SharedPtr<AVertexBuffer> AllocateVertexBuffer(EBufferType type = EBufferType::DYNAMIC_BUFFER);

        void ReleaseObject(SharedPtr<IObjectGPU> buffer);


    private:
        SharedPtr<IGraphicObjectsFactory> m_factory;

        HashMap<void*, SharedPtr<AVertexBuffer>> m_vertexBuffers;
    };
}

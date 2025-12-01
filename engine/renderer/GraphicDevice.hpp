#pragma once

#include <utility/Definitions.hpp>

#include <renderer/pipeline/GraphicAPI.hpp>
#include <renderer/buffers/ObjectGPU.hpp>


namespace Kiwi {
    KIWI_INTERFACE IGraphicObjectsFactory;

    KIWI_ABSTRACT class ARenderInstance;

    KIWI_ABSTRACT class ARenderPipeline;
    KIWI_ABSTRACT class AVertexBuffer;


    // TODO: Should it manage **global** and **shared** buffers: UBO, SSBO and so on?
    KIWI_ABSTRACT class GraphicDevice {
    public:
        explicit GraphicDevice(SharedPtr<IGraphicObjectsFactory> factoryPtr);

        KIWI_NODISCARD EGraphicAPI GetCurrentSelectedAPI();

        KIWI_NODISCARD SharedPtr<AVertexBuffer> AllocateVertexBuffer(EBufferType type = EBufferType::DYNAMIC_BUFFER);

        void ReleaseObject(SharedPtr<IObjectGPU> buffer);


    private:
        SharedPtr<IGraphicObjectsFactory> m_factory;

        HashMap<void*, SharedPtr<AVertexBuffer>> m_vertexBuffers;
    };
}

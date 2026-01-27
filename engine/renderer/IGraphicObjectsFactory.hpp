#pragma once

#include <types/TypeTraits.hpp>


namespace Kiwi {
    KIWI_FORWARD_DECLARATIONS(
        KIWI_ABSTRACT class AGraphicDevice;
        KIWI_ABSTRACT class ARenderPipeline;
        KIWI_ABSTRACT class AShaderCompiler;

        class GraphicDevice;
    )



    KIWI_INTERFACE IGraphicObjectsFactory {
    public:
        KIWI_NODISCARD static SharedPtr<IGraphicObjectsFactory> Create();

    public:
        KIWI_NODISCARD virtual SharedPtr<AGraphicDevice> CreateGraphicDevice() const = 0;
        KIWI_NODISCARD virtual SharedPtr<ARenderPipeline> CreateRenderPipeline() const = 0;
        KIWI_NODISCARD virtual SharedPtr<AShaderCompiler> CreateShaderCompiler() const = 0;


        virtual ~IGraphicObjectsFactory() = default;
    };
}

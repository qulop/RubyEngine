#pragma once

#include <types/TypeTraits.hpp>

#include "types/Logger.hpp"


namespace Ruby {
    RUBY_FORWARD_DECLARATIONS(
        RUBY_ABSTRACT class ARenderInstance;
        RUBY_ABSTRACT class ARenderPipeline;
        RUBY_ABSTRACT class AShaderCompiler;

        class GraphicDevice;
    )



    RUBY_INTERFACE IGraphicObjectsFactory {
    public:
        RUBY_NODISCARD static SharedPtr<IGraphicObjectsFactory> Create();

    public:
        RUBY_NODISCARD virtual SharedPtr<ARenderInstance> CreateRenderInstance() const = 0;
        RUBY_NODISCARD virtual SharedPtr<ARenderPipeline> CreateRenderPipeline(const SharedPtr<GraphicDevice>& device) const = 0;
        RUBY_NODISCARD virtual SharedPtr<AShaderCompiler> CreateShaderCompiler() const = 0;


        virtual ~IGraphicObjectsFactory() = default;
    };
}

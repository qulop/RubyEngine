#include "GraphicObjectsFactoryGL.hpp"

#include <backends/opengl/pipeline/ContextGL.hpp>
#include <backends/opengl/pipeline/RenderPipelineGL.hpp>
#include <backends/opengl/shaders/ShaderCompilerGL.hpp>



namespace Kiwi::OpenGL {
    SharedPtr<ARenderInstance> GraphicObjectsFactoryGL::CreateRenderInstance() const {
        return MakeShared<ContextGL>();
    }

    SharedPtr<ARenderPipeline> GraphicObjectsFactoryGL::CreateRenderPipeline(const SharedPtr<GraphicDevice>& device) const {
        return MakeShared<RenderPipelineGL>(device);
    }

    SharedPtr<AShaderCompiler> GraphicObjectsFactoryGL::CreateShaderCompiler() const {
        return MakeShared<ShaderCompilerGL>();
    }
}

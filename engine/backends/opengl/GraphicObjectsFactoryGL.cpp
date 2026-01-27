#include "GraphicObjectsFactoryGL.hpp"

#include <backends/opengl/RenderContextGL.hpp>
#include <backends/opengl/pipeline/RenderPipelineGL.hpp>
#include <backends/opengl/shaders/ShaderCompilerGL.hpp>



namespace Kiwi::OpenGL {
    SharedPtr<ARenderPipeline> GraphicObjectsFactoryGL::CreateRenderPipeline() const {
        return MakeShared<RenderPipelineGL>();
    }

    SharedPtr<AShaderCompiler> GraphicObjectsFactoryGL::CreateShaderCompiler() const {
        return MakeShared<ShaderCompilerGL>();
    }
}

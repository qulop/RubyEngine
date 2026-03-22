#include "GraphicObjectsFactoryGL.hpp"

#include <backends/opengl/RenderContextGL.hpp>
#include <backends/opengl/shaders/ShaderCompilerGL.hpp>



namespace Kiwi::OpenGL {
    SharedPtr<AShaderCompiler> GraphicObjectsFactoryGL::CreateShaderCompiler() const {
        return MakeShared<ShaderCompilerGL>();
    }
}

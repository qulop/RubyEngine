#pragma once

#include <renderer/shaders/ShaderCompiler.hpp>


namespace Kiwi::Vulkan {
    class ShaderCompilerVK : public AShaderCompiler {
        KIWI_CREATE_OBJECT(ShaderCompilerVK, AShaderCompiler);

    public:
        KIWI_NODISCARD UniquePtr<AShader> CompileFile(const File& sourceFile) override;

        ~ShaderCompilerVK() override = default;
    };
}

#include "ShaderCompilerVK.hpp"


namespace Kiwi::Vulkan {
    UniquePtr<AShader> ShaderCompilerVK::CompileFile(const File& sourceFile) {
        const auto spirV = PreprocessAndCompileToSpirV(sourceFile, ESpirVEnvironment::Vulkan, ESpirVOptimizationLevel::PERFORMANCE);
        if (spirV) {

        }

        return nullptr;
    }

}
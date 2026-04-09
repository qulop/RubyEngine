#pragma once

#include "Shader.hpp"

#include <common/meta/TypeTraits.hpp>
#include <common/types/Result.hpp>


namespace Kiwi {
    enum class ESpirVOptimizationLevel {
        ZERO,
        REDUCE_SIZE,
        PERFORMANCE
    };

    enum class ESpirVEnvironment {
        NONE,
        OpenGL, Vulkan
    };


    class SpirV {
    private:
        struct ShaderProcessDetails {
            EShaderStage stage = EShaderStage::NONE;
            String src;
            String outputFile;
            ESpirVEnvironment environment = ESpirVEnvironment::NONE;
        };

    public:
        struct PreprocessDetails : ShaderProcessDetails {
            std::span<StringView> macroList;
        };

        struct CompilationDetails : ShaderProcessDetails {
            ESpirVOptimizationLevel optimizationLevel = ESpirVOptimizationLevel::ZERO;
        };

    public:
        KIWI_NODISCARD static Result<String> PreprocessGLSL(const PreprocessDetails& details);

        KIWI_NODISCARD static Result<Vector<u32>> CompileGLSL(const CompilationDetails& details);
    };
}
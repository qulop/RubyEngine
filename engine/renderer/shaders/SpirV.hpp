#pragma once

#include "Shader.hpp"

#include <types/TypeTraits.hpp>


namespace Kiwi {
    enum class ESpirVOptimizationLevel {
        ZERO,
        REDUCE_SIZE,
        PERFORMANCE
    };

    enum class ESpirVEnviroment {
        NONE,
        OpenGL, Vulkan
    };


    class SpirV {
    private:
        struct ShaderProcessDetails {
            EShaderStage stage = EShaderStage::NONE;
            String src;
            String outputFile;
            ESpirVEnviroment enviroment = ESpirVEnviroment::NONE;
        };

    public:
        struct PreprocessDetails : ShaderProcessDetails {
            std::span<StringView> macroList;
        };

        struct CompilationDetails : ShaderProcessDetails {
            ESpirVOptimizationLevel optimizationLevel = ESpirVOptimizationLevel::ZERO;
        };

    public:
        KIWI_NODISCARD static Opt<String> PreprocessGLSL(const PreprocessDetails& details);

        KIWI_NODISCARD static Opt<Vector<u32>> CompileGLSL(const CompilationDetails& details);
    };
}
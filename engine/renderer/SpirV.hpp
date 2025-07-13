#pragma once

#include "Shader.hpp"

#include <types/TypeTraits.hpp>


namespace Ruby {
    enum class SpirVOptimizationLevel {
        ZERO,
        REDUCE_SIZE,
        PERFORMANCE
    };

    enum class SpirVEnviroment {
        NONE,
        OpenGL, Vulkan
    };


    class SpirV {
    public:
        struct PreprocessDetails {
            ShaderStage stage = ShaderStage::NONE;
            std::string_view src;
            std::string_view outputFile;
            SpirVEnviroment enviroment = SpirVEnviroment::NONE;
        };

        struct CompilationDetails : PreprocessDetails {
            SpirVOptimizationLevel optimizationLevel = SpirVOptimizationLevel::ZERO;
        };

    public:
        RUBY_NODISCARD static Opt<String> PreprocessGLSL(const PreprocessDetails& details);

        RUBY_NODISCARD static Opt<Vector<u32>> CompileGLSL(const CompilationDetails& details);

    };
}
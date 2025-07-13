#include "SpirV.hpp"

#include <types/Logger.hpp>
#include <utility/Assert.hpp>

#include <shaderc/shaderc.hpp>


namespace {
    const char* const GLSL_MACRO_OPENGL_IN_USE = "GLSL_OPENGL";
    const char* const GLSL_MACRO_VULKAN_IN_USE = "GLSL_VULKAN";


    Ruby::Opt<shaderc_shader_kind> rubyShaderStageToShaderC(Ruby::ShaderStage stage) {
        using namespace Ruby;

        switch (stage) {
            case ShaderStage::VERTEX:
                return shaderc_vertex_shader;
            case ShaderStage::TESS_CONTROL:
                return shaderc_tess_control_shader;
            case ShaderStage::TESS_EVALUATION:
                return shaderc_tess_evaluation_shader;
            case ShaderStage::GEOMETRY:
                return shaderc_geometry_shader;
            case ShaderStage::FRAGMENT:
                return shaderc_fragment_shader;
            case ShaderStage::COMPUTE:
                return shaderc_compute_shader;
            default:
                RUBY_ERROR("rubyShaderStageToShadercShaderKind() : Unknown stage received.");
                return nullopt;
        }
    }

    Ruby::Opt<shaderc_optimization_level> rubySpirVOptimizationLevelToShaderC(Ruby::SpirVOptimizationLevel lvl) {
        using namespace Ruby;
        
        switch (lvl) {
            case SpirVOptimizationLevel::ZERO:
                return shaderc_optimization_level_zero;
            case SpirVOptimizationLevel::REDUCE_SIZE:
                return shaderc_optimization_level_size;
            case SpirVOptimizationLevel::PERFORMANCE:
                return shaderc_optimization_level_performance;
            default:
                RUBY_ERROR("rubySpirVOptimizationLevelToShaderC() : Unknown optimization level received.");
                return nullopt;
        }
    }

    Ruby::Opt<shaderc::CompileOptions> getCompileOptions(Ruby::SpirVEnviroment env, Ruby::SpirVOptimizationLevel optLvl) {
        using namespace Ruby;

        RUBY_ASSERT_BASIC(env != Ruby::SpirVEnviroment::NONE);
        
        auto shadercOptLevel = rubySpirVOptimizationLevelToShaderC(optLvl);
        if (!shadercOptLevel) {
            return nullopt;
        }
        
        shaderc::CompileOptions options;
        
        options.SetOptimizationLevel(shadercOptLevel.value());
        if (env == SpirVEnviroment::OpenGL) {
            options.AddMacroDefinition(GLSL_MACRO_OPENGL_IN_USE);
        }
        else {
            options.AddMacroDefinition(GLSL_MACRO_VULKAN_IN_USE);
        }
        

        return options;
    }
}


namespace Ruby {
    Opt<String> SpirV::PreprocessGLSL(const PreprocessDetails& details) {
        auto shadercKind = rubyShaderStageToShaderC(details.stage);
        if (!shadercKind) {
            return nullopt;
        }


        shaderc::Compiler compiler;
        auto compileOptions = getCompileOptions(details.enviroment, SpirVOptimizationLevel::ZERO);
        if (!compileOptions) {
            return nullopt;
        }

        auto result = compiler.PreprocessGlsl(
            details.src.data(), details.src.size(),
            shadercKind.value(), 
            details.outputFile.data(), 
            compileOptions.value()
        );
        if (result.GetCompilationStatus() != shaderc_compilation_status_success) {
            RUBY_ERROR("SpirV::CompileGLSL() : {}", result.GetErrorMessage());
            return nullopt;
        }
        
        return String{ result.begin(), result.end() };
    }


    Opt<Vector<u32>> SpirV::CompileGLSL(const CompilationDetails& details) {
        RUBY_ASSERT_BASIC(details.enviroment == SpirVEnviroment::OpenGL || details.enviroment == SpirVEnviroment::Vulkan);

        auto shadercKind = rubyShaderStageToShaderC(details.stage);
        if (!shadercKind) {
            return nullopt;
        }

        shaderc::Compiler compiler;
        auto compileOptions = getCompileOptions(details.enviroment, details.optimizationLevel);
        if (!compileOptions) {
            return nullopt;
        }


        auto result = compiler.CompileGlslToSpv(
            details.src.data(), details.src.size(),
            shadercKind.value(),
            details.outputFile.data(),
            compileOptions.value()
        );
        if (result.GetCompilationStatus() != shaderc_compilation_status_success) {
            RUBY_ERROR("SpirV::CompileGLSL() : {}", result.GetErrorMessage());
            return nullopt;
        }

        return Vector<u32>{ result.begin(), result.end() };
    }
}
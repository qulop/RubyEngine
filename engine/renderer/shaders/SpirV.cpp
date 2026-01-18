#include "SpirV.hpp"

#include <utility/Assert.hpp>

#include <shaderc/shaderc.hpp>


namespace {
    const char* const GLSL_MACRO_OPENGL_IN_USE = "GLSL_OPENGL";
    const char* const GLSL_MACRO_VULKAN_IN_USE = "GLSL_VULKAN";


    shaderc_optimization_level ESpirVOptimizationLevelToShaderC(Kiwi::ESpirVOptimizationLevel lvl) {
        using namespace Kiwi;
        
        switch (lvl) {
            case ESpirVOptimizationLevel::ZERO:
                return shaderc_optimization_level_zero;
            case ESpirVOptimizationLevel::REDUCE_SIZE:
                return shaderc_optimization_level_size;
            case ESpirVOptimizationLevel::PERFORMANCE:
                return shaderc_optimization_level_performance;
            default:
                std::unreachable();
        }
    }

    shaderc::CompileOptions GetCompileOptions(Kiwi::ESpirVEnviroment env, Kiwi::ESpirVOptimizationLevel optLvl) {
        using namespace Kiwi;

        auto shadercOptLevel = ESpirVOptimizationLevelToShaderC(optLvl);

        shaderc::CompileOptions options;
        
        options.SetOptimizationLevel(shadercOptLevel);
        if (env == ESpirVEnviroment::OpenGL) {
            options.AddMacroDefinition(GLSL_MACRO_OPENGL_IN_USE);
        }
        else {
            options.AddMacroDefinition(GLSL_MACRO_VULKAN_IN_USE);
        }
        

        return options;
    }
}


namespace Kiwi {
    Result<String, EGeneralError> SpirV::PreprocessGLSL(const PreprocessDetails& details) {
        auto shadercKind = Cast<EShaderStage>::ToShaderCKind(details.stage);

        shaderc::Compiler compiler;
        auto compileOptions = GetCompileOptions(details.enviroment, ESpirVOptimizationLevel::ZERO);

        auto result = compiler.PreprocessGlsl(
            details.src.data(), details.src.size(),
            shadercKind,
            details.outputFile.data(), 
            compileOptions
        );
        if (result.GetCompilationStatus() != shaderc_compilation_status_success) {
            return Unexpected(Error{
                .kind = EGeneralError::COMPILE_ERROR,
                .desc = result.GetErrorMessage()
            });
        }
        
        return String{ result.begin(), result.end() };
    }


    Result<Vector<u32>, EGeneralError> SpirV::CompileGLSL(const CompilationDetails& details) {
        KIWI_ASSERT_BASIC(details.enviroment == ESpirVEnviroment::OpenGL || details.enviroment == ESpirVEnviroment::Vulkan);

        auto shadercKind = Cast<EShaderStage>::ToShaderCKind(details.stage);

        shaderc::Compiler compiler;
        auto compileOptions = GetCompileOptions(details.enviroment, details.optimizationLevel);

        auto result = compiler.CompileGlslToSpv(
            details.src.data(), details.src.size(),
            shadercKind,
            details.outputFile.data(),
            compileOptions
        );
        if (result.GetCompilationStatus() != shaderc_compilation_status_success) {
            return Unexpected(Error{
              .kind = EGeneralError::COMPILE_ERROR,
              .desc = result.GetErrorMessage()
            });
        }

        return Vector<u32>{ result.begin(), result.end() };
    }
}
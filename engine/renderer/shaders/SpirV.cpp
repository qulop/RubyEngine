#include "SpirV.hpp"

#include <common/Assert.hpp>
#include <common/types/Result.hpp>

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

    shaderc::CompileOptions GetCompileOptions(Kiwi::ESpirVEnvironment env, Kiwi::ESpirVOptimizationLevel optLvl) {
        using namespace Kiwi;

        auto shadercOptLevel = ESpirVOptimizationLevelToShaderC(optLvl);

        shaderc::CompileOptions options;
        
        options.SetOptimizationLevel(shadercOptLevel);
        if (env == ESpirVEnvironment::OpenGL) {
            options.AddMacroDefinition(GLSL_MACRO_OPENGL_IN_USE);
        }
        else {
            options.AddMacroDefinition(GLSL_MACRO_VULKAN_IN_USE);
        }
        

        return options;
    }
}


namespace Kiwi {
    Result<String> SpirV::PreprocessGLSL(const PreprocessDetails& details) {
        auto shadercKind = Cast<EShaderStage>::ToShaderCKind(details.stage);

        shaderc::Compiler compiler;
        auto compileOptions = GetCompileOptions(details.environment, ESpirVOptimizationLevel::ZERO);

        auto result = compiler.PreprocessGlsl(
            details.src.data(), details.src.size(),
            shadercKind,
            details.outputFile.data(), 
            compileOptions
        );
        if (result.GetCompilationStatus() != shaderc_compilation_status_success) {
            return Error {
                .kind = EGeneralError::COMPILE_ERROR,
                .desc = result.GetErrorMessage()
            };
        }

        return Success(
            String { result.begin(), result.end() }
        );
    }


    Result<Vector<u32>> SpirV::CompileGLSL(const CompilationDetails& details) {
        KIWI_ASSERT_BASIC(details.environment == ESpirVEnvironment::OpenGL || details.environment == ESpirVEnvironment::Vulkan);

        auto shadercKind = Cast<EShaderStage>::ToShaderCKind(details.stage);

        shaderc::Compiler compiler;
        auto compileOptions = GetCompileOptions(details.environment, details.optimizationLevel);

        auto result = compiler.CompileGlslToSpv(
            details.src.data(), details.src.size(),
            shadercKind,
            details.outputFile.data(),
            compileOptions
        );
        if (result.GetCompilationStatus() != shaderc_compilation_status_success) {
            return Error {
                .kind = EGeneralError::COMPILE_ERROR,
                .desc = result.GetErrorMessage()
            };
        }

        return Success(
            Vector<u32> { result.begin(), result.end() }
        );
    }
}
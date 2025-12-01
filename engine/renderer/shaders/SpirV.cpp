#include "SpirV.hpp"

#include <types/Logger.hpp>
#include <utility/Assert.hpp>

#include <shaderc/shaderc.hpp>


namespace {
    const char* const GLSL_MACRO_OPENGL_IN_USE = "GLSL_OPENGL";
    const char* const GLSL_MACRO_VULKAN_IN_USE = "GLSL_VULKAN";


    Kiwi::Opt<shaderc_optimization_level> ESpirVOptimizationLevelToShaderC(Kiwi::ESpirVOptimizationLevel lvl) {
        using namespace Kiwi;
        
        switch (lvl) {
            case ESpirVOptimizationLevel::ZERO:
                return shaderc_optimization_level_zero;
            case ESpirVOptimizationLevel::REDUCE_SIZE:
                return shaderc_optimization_level_size;
            case ESpirVOptimizationLevel::PERFORMANCE:
                return shaderc_optimization_level_performance;
            default:
                KIWI_ERROR("ESpirVOptimizationLevelToShaderC() : Unknown optimization level received.");
                return nullopt;
        }
    }

    Kiwi::Opt<shaderc::CompileOptions> GetCompileOptions(Kiwi::ESpirVEnviroment env, Kiwi::ESpirVOptimizationLevel optLvl) {
        using namespace Kiwi;

        auto shadercOptLevel = ESpirVOptimizationLevelToShaderC(optLvl);
        if (!shadercOptLevel) {
            return nullopt;
        }
        
        shaderc::CompileOptions options;
        
        options.SetOptimizationLevel(shadercOptLevel.value());
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
    Opt<String> SpirV::PreprocessGLSL(const PreprocessDetails& details) {
        auto shadercKind = Cast<EShaderStage>::ToShaderCKind(details.stage);
        if (!shadercKind) {
            return nullopt;
        }


        shaderc::Compiler compiler;
        auto compileOptions = GetCompileOptions(details.enviroment, ESpirVOptimizationLevel::ZERO);
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
            KIWI_ERROR("SpirV::CompileGLSL() : {}", result.GetErrorMessage());
            return nullopt;
        }
        
        return String{ result.begin(), result.end() };
    }


    Opt<Vector<u32>> SpirV::CompileGLSL(const CompilationDetails& details) {
        KIWI_ASSERT_BASIC(details.enviroment == ESpirVEnviroment::OpenGL || details.enviroment == ESpirVEnviroment::Vulkan);

        auto shadercKind = Cast<EShaderStage>::ToShaderCKind(details.stage);
        if (!shadercKind) {
            return nullopt;
        }

        shaderc::Compiler compiler;
        auto compileOptions = GetCompileOptions(details.enviroment, details.optimizationLevel);
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
            KIWI_ERROR("SpirV::CompileGLSL() : {}", result.GetErrorMessage());
            return nullopt;
        }

        return Vector<u32>{ result.begin(), result.end() };
    }
}
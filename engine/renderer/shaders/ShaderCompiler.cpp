#include "ShaderCompiler.hpp"

#include <renderer/shaders/SpirV.hpp>



namespace Kiwi {
    Opt<PreprocessorGLSL::SourcesMap> AShaderCompiler::PreprocessSource(const String& src) {
        PreprocessorGLSL preprocessor;

        auto res = preprocessor.Preprocess(src);
        if (res) {
            return *res;
        }

        auto kind = res.error().kind;
        KIWI_ASSERT_BASIC(kind != GlslPreprocessError::NONE);

        // TODO: Idk where am i should output error messages, so for now just skip it
        switch (kind) {
            case GlslPreprocessError::INCORRECT_STAGE_NAME:
                break;
            case GlslPreprocessError::END_OF_STAGE_MISSED:
                break;
            case GlslPreprocessError::TOKEN_ALREADY_DECLARED:
                break;
            case GlslPreprocessError::INCORRECT_PREPROCESSOR_PROPERTIES_COUNT:
                break;
        }

        return nullopt;
    }

    Result<AShaderCompiler::CompiledSpirVMap, EGeneralError> AShaderCompiler::CompileToSpirV(const CompilationDetails& compilationDetails) {
        Map<EShaderStage, Vector<u32>> result;

        for (const auto& [stage, src] : compilationDetails.preprocessedSrc) {
            SpirV::CompilationDetails details;
            details.stage = stage;
            details.src = src;
            details.environment = compilationDetails.environment;
            details.optimizationLevel = compilationDetails.optimizationLvl;


            if (auto r = SpirV::CompileGLSL(details)) {
                result[stage] = *r;
            }
            else {
                // TODO
            }
        }

        return result;
    }

    Result<AShaderCompiler::CompiledSpirVMap, EGeneralError> AShaderCompiler::PreprocessAndCompileToSpirV(const File& sourceFile, ESpirVEnvironment env, ESpirVOptimizationLevel optimizationLvl) {
        FileContent src = sourceFile.ReadAll().value_or(FileContent{});
        if (src.IsEmpty()) {
            // TODO
        }

        if (const auto preprocessedSrc = PreprocessSource(src.GetAsString())) {
            CompilationDetails d;
            d.environment = env;
            d.optimizationLvl = optimizationLvl;
            d.preprocessedSrc = *preprocessedSrc;

            if (auto compiledSpirV = CompileToSpirV(d)) {
                return compiledSpirV;
            }
            else {

            }
        }
        else {

        }
    }
}

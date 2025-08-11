#include "Shader.hpp"

#include "PreprocessorGLSL.hpp"

#include <utility/Algorithm.hpp>
#include <types/Logger.hpp>


namespace Ruby {
    Opt<ShaderStage> Shader::StringToShaderStage(StringView stageName) {
        if      (stageName == "vertex")     return ShaderStage::VERTEX;
        else if (stageName == "geometry")   return ShaderStage::GEOMETRY;
        else if (stageName == "fragment")   return ShaderStage::FRAGMENT;
        else if (stageName == "compute")    return ShaderStage::COMPUTE;

        return nullopt;
    }

    Opt<Shader::UncompiledSourcesMap> Shader::PreprocessSource(const String& src) const {
        PreprocessorGLSL preprocessor;

        auto res = preprocessor.TryPreprocess(src);
        if (res) {
            return *res;
        }
        
        auto kind = res.error().kind;
        RUBY_ASSERT_BASIC(kind != GlslPreprocessError::NONE);

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
}
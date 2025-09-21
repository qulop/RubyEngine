#include "Shader.hpp"

#include <renderer/shaders/PreprocessorGLSL.hpp>
#include <renderer/shaders/ShaderCacheManager.hpp>

#include <utility/Algorithm.hpp>

#include <types/Logger.hpp>
#include <types/Hash.hpp>


namespace Ruby {
    Opt<EShaderStage> AShader::StringToShaderStage(StringView stageName) {
        if      (stageName == "vertex")     return EShaderStage::VERTEX;
        else if (stageName == "geometry")   return EShaderStage::GEOMETRY;
        else if (stageName == "fragment")   return EShaderStage::FRAGMENT;
        else if (stageName == "compute")    return EShaderStage::COMPUTE;

        return nullopt;
    }

    Opt<AShader::UncompiledSourcesMap> AShader::PreprocessSource(const String& src) const {
        PreprocessorGLSL preprocessor;

        auto res = preprocessor.Preprocess(src);
        if (res) {
            return *res;
        }
        
        auto kind = res.error().kind;
        RUBY_ASSERT_BASIC(kind != GlslPreprocessError::NONE);

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

    Opt<ShaderCacheEntry> AShader::TryToGetCachedShader(const String& hashedShaderSource) const {
         auto& shaderCacheManager = ShaderCacheManager::GetInstance();

        Opt<ShaderCacheEntry> optCacheEntry = shaderCacheManager
            .GetFromLocalCache(hashedShaderSource)
            .or_else([&]() 
            {
                return shaderCacheManager
                    .GetFromGlobalCache(hashedShaderSource)
                    .transform(&ShaderCacheEntry::FromFileContent);
            }
        );

        if (!optCacheEntry) {
            return nullopt; 
        }

        ShaderCacheEntry& cacheEntry = optCacheEntry.value();
        if (!shaderCacheManager.IsInLocalCache(hashedShaderSource)) {
            if (!shaderCacheManager.AddToLocalCache(hashedShaderSource, cacheEntry)) RUBY_UNLIKELY {
                RUBY_ERROR("ShaderGL::CompileShader() : Failed to add cache entry into the local cache");
            }
        }

        RUBY_DEBUG("AShader::TryToGetCachedShader() : The shader \"{}\" successfully loaded from the cache",
            hashedShaderSource
        );

        return cacheEntry;
    }
}
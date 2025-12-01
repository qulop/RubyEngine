#include "ShaderCompilerGL.hpp"

#include <renderer/shaders/SpirV.hpp>
#include <renderer/shaders/ShaderCacheManager.hpp>

#include "ShaderGL.hpp"


namespace {
    void releaseShaderResources(Kiwi::OpenGL::GlID programId, const Kiwi::HashMap<Kiwi::EShaderStage, Kiwi::OpenGL::GlID> modules) {
        for (const auto& [stage, id] : modules) {
            glDeleteShader(id);
        }
        glDeleteProgram(programId);
    }
}


namespace Kiwi::OpenGL {
    UniquePtr<AShader> ShaderCompilerGL::CompileFile(const File& sourceFile) {
        auto src = sourceFile.ReadAll().value_or(FileContent{});
        if (src.IsEmpty()) {
            return nullptr;
        }

        auto optPreprocessedSrc = ShaderCompilerGL::PreprocessSource(src.GetAsString());
        if (!optPreprocessedSrc) {
            return nullptr;
        }

        bool completedWithoutErrors = true;
        HashMap<EShaderStage, GlID> shaderModules;
        GlID shaderProgramId = glCreateProgram();

        for (const auto& [stage, src] : *optPreprocessedSrc) {
            GlID id = CompileShaderStage(stage, src);
            if (id == KIWI_GL_UNDEFINED_ID) {
                completedWithoutErrors = false;
                continue;
            }

            shaderModules[stage] = id;
            glAttachShader(shaderProgramId, id);
        }

        if (!completedWithoutErrors) {
            releaseShaderResources(shaderProgramId, shaderModules);
            return nullptr;
        }

        glLinkProgram(shaderProgramId);
        if (!ShaderCompilerGL::CheckCompilationOrLinkingResult(shaderProgramId, EShaderStage::SHADER_PROGRAM)) {
            releaseShaderResources(shaderProgramId, shaderModules);
            return nullptr;
        }

        for (const auto& [_, id] : shaderModules) {
            glDetachShader(shaderProgramId, id);
        }

        return UniquePtr<ShaderGL>(new ShaderGL(shaderProgramId, std::move(shaderModules)));
    }

    bool ShaderCompilerGL::CheckCompilationOrLinkingResult(GLuint target, EShaderStage type) {
        GLint hasNoErrors = 0;
        bool isProgramReceived = (type == EShaderStage::SHADER_PROGRAM);

        if (isProgramReceived) {
            glGetProgramiv(target, GL_LINK_STATUS, &hasNoErrors);
        }
        else {
            glGetShaderiv(target, GL_COMPILE_STATUS, &hasNoErrors);
        }

        if (hasNoErrors) {
            return true;
        }

        GLchar buffer[256] = { '\0' };
        auto bufferSize = BasicCast::To<GLsizei>(std::size(buffer));
        if (isProgramReceived) {
            glGetProgramInfoLog(target, bufferSize, nullptr, buffer);
        }
        else {
            glGetShaderInfoLog(target, bufferSize, nullptr, buffer);
        }

        KIWI_ERROR("ShaderCompilerGL::CheckCompilationOrLinkingResult : An error occurred while {} shader. {}",
            (isProgramReceived) ? "linking" : "compiling",
            buffer
        );

        return false;
    }

    GlID ShaderCompilerGL::CompileShaderStage(EShaderStage stage, StringView src) const {
        KIWI_ASSERT(stage != EShaderStage::SHADER_PROGRAM && stage != EShaderStage::NONE,
                    "Either EShaderStage::SHADER_PROGRAM or EShaderStage::NONE passed here"
        );

        auto hashedShaderSource = Hash64::FromData(src).value_or(Hash64{});
        if (hashedShaderSource.IsEmpty()) {
            KIWI_ERROR("ShaderCompilerGL::CompileShaderStage() : Failed to cast integer hash of the shader source into the string");
            return KIWI_GL_UNDEFINED_ID;
        }

        auto& shaderCacheManager = ShaderCacheManager::GetInstance();
        if (auto shaderCacheEntry = shaderCacheManager.TryToFindCachedShader(hashedShaderSource); shaderCacheEntry) {
            if (!shaderCacheManager.IsInLocalCache(hashedShaderSource)) {
                if (!shaderCacheManager.AddToLocalCache(hashedShaderSource, shaderCacheEntry.value())) KIWI_UNLIKELY {
                    KIWI_ERROR("ShaderCompilerGL::CompileShaderStage() : Failed to add cache entry into the local cache");
                }
            }

            return CreateFromSpirVByteCode(stage, "main", shaderCacheEntry.value().spriVByteCode);
        }


        auto outputFilePath = shaderCacheManager.GetCacheDirAbsolutePath() / hashedShaderSource.ToString();

        SpirV::CompilationDetails cDetails;
        cDetails.stage = stage;
        cDetails.src = src;
        cDetails.enviroment = ESpirVEnviroment::OpenGL;
        cDetails.optimizationLevel = ESpirVOptimizationLevel::PERFORMANCE;
        cDetails.outputFile = outputFilePath.string();

        Vector<u32> byteCode = SpirV::CompileGLSL(cDetails).value_or(Vector<u32>{});
        GlID id = CreateFromSpirVByteCode(stage, "main", byteCode);
        if (id == KIWI_GL_UNDEFINED_ID) {
            return KIWI_GL_UNDEFINED_ID;
        }

        if (!shaderCacheManager.AddToCache(hashedShaderSource, ShaderCacheEntry{ byteCode })) KIWI_UNLIKELY {
            KIWI_WARNING("ShaderCompilerGL::CompileShaderStage() : Failed to add {} in to the local or global cache!",
                hashedShaderSource
            );
        }

        return id;
    }


    GlID ShaderCompilerGL::CreateFromSpirVByteCode(EShaderStage stage, StringView entryPoint, const Vector<u32>& byteCode) const {
        if (byteCode.empty()) {
            return KIWI_GL_UNDEFINED_ID;
        }

        GlID id = glCreateShader(Cast<EShaderStage>::ToGLenum(stage).value_or(KIWI_GL_UNDEFINED_ID));

        glShaderBinary(1, &id,
                        GL_SHADER_BINARY_FORMAT_SPIR_V, byteCode.data(),
                        BasicCast::To<GLsizei>(byteCode.size() * sizeof(u32))
        );
        glSpecializeShader(id, entryPoint.data(), 0, nullptr, nullptr);


        if (!CheckCompilationOrLinkingResult(id, stage)) {
            glDeleteShader(id);
            return KIWI_GL_UNDEFINED_ID;
        }

        return id;
    }
}

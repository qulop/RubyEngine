#include "ShaderGL.hpp"

#include <utility/Algorithm.hpp>
#include <utility/Assert.hpp>

#include <types/Cast.hpp>
#include <types/Logger.hpp>
#include <types/File.hpp>

#include <renderer/shaders/SpirV.hpp>
#include <renderer/shaders/ShaderCacheManager.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>



namespace {
    bool hasShaderProcessError(GLuint target, Ruby::EShaderStage type) {
        using namespace Ruby;

        GLint hasNoErrors = 0;
        bool isProgramReceived = (type == EShaderStage::SHADER_PROGRAM);

        if (isProgramReceived) {
            glGetProgramiv(target, GL_LINK_STATUS, &hasNoErrors);
        }
        else {
             glGetShaderiv(target, GL_COMPILE_STATUS, &hasNoErrors);
        }

        if (hasNoErrors) {
            return false;
        }

        GLchar buffer[256] = { '\0' };
        auto bufferSize = static_cast<GLsizei>(std::size(buffer));
        switch (isProgramReceived) {
            case true:
                glGetProgramInfoLog(target, bufferSize, nullptr, buffer);
                break;
            case false:
                glGetShaderInfoLog(target, bufferSize, nullptr, buffer);
                break;
        }

        RUBY_ERROR("hasShaderProcessError() : An error occurred while {} shader. {}", 
                   (isProgramReceived) ? "linking" : "compiling",
                   buffer
        );

        return true;
    }
}


namespace Ruby::OpenGL {
    void* ShaderGL::GetNativePipelineHandle() {
        return &m_programId;
    }

    const void* ShaderGL::GetNativePipelineHandle() const {
        return GetNativePipelineHandle();
    }


    void* ShaderGL::GetNativeShaderModuleHandle(EShaderStage stage) {
        if (!m_shadersId.contains(stage)) {
            return nullptr;
        }
        return &m_shadersId.at(stage);
    }

    const void* ShaderGL::GetNativeShaderModuleHandle(EShaderStage stage) const {
        return GetNativeShaderModuleHandle(stage);
    }

    u32 ShaderGL::GetUniformLocation(const char* name) const {
        return glGetUniformLocation(m_programId, name);
    }

    void ShaderGL::Bind() const {
        glUseProgram(m_programId);
    }

    void ShaderGL::Unbind() const {
        glUseProgram(0);
    }

    void ShaderGL::AddShader(EShaderStage stage, const String& path, bool overrideExistingStage) {
        if (m_sourcesToCompile.get() == nullptr) {
            m_sourcesToCompile = makeUnique<UncompiledSourcesMap>();
        }

        if (overrideExistingStage) {
            m_sourcesToCompile->emplace(stage, path);
        }
        else {
            m_sourcesToCompile->try_emplace(stage, path);
        }
    }

    void ShaderGL::AddShader(const String& src, bool overrideExistingStage) {
        auto optPreprocessedSrc = PreprocessSource(src);
        if (!optPreprocessedSrc) {
            return;
        }

        for (const auto& [stage, stageSource] : *optPreprocessedSrc) {
            AddShader(stage, stageSource, overrideExistingStage);
        }
    }

    bool ShaderGL::IsEmpty() const {
        return m_shadersId.empty() && m_programId == RUBY_GL_UNDEFINED_ID;
    }

    bool ShaderGL::IsReady() const {
        return m_isReady;
    }

    void ShaderGL::Compile() {
        bool completedWithoutErrors = true;

        m_programId = glCreateProgram();
        for (const auto& [stage, src] : *m_sourcesToCompile) {
            GlID id = CompileShader(stage, src.data());
            if (id == RUBY_GL_UNDEFINED_ID) {
                completedWithoutErrors = false;
                continue;
            }

            m_shadersId[stage] = id;
            glAttachShader(m_programId, id);
        }

        m_sourcesToCompile.reset();
        if (!completedWithoutErrors) {
            return;
        }

        glLinkProgram(m_programId);
        if (hasShaderProcessError(m_programId, EShaderStage::SHADER_PROGRAM)) {
            return;
        }

        m_isReady = true;
    }

    void ShaderGL::SetFloat(const char* uniName, f32 value) const {
        glUniform1f(GetUniformLocation(uniName), value);
    }

    void ShaderGL::SetFloat2(const char* uniName, const glm::vec2& vec) const {
        glUniform2f(GetUniformLocation(uniName), vec.x, vec.y);
    }

    void ShaderGL::SetFloat3(const char* uniName, const glm::vec3& vec) const {
        glUniform3f(GetUniformLocation(uniName), vec.x, vec.y, vec.z);
    }

    void ShaderGL::SetFloat4(const char* uniName, const glm::vec4& vec) const {
        glUniform4f(GetUniformLocation(uniName), vec.x, vec.y, vec.z, vec.w);
    }

    void ShaderGL::SetFloatVector(const char* uniName, const f32* data, i32 count) const {
        glUniform1fv(GetUniformLocation(uniName), count, data);
    }

    void ShaderGL::SetInt(const char* uniName, i32 value) const {
        glUniform1i(GetUniformLocation(uniName), value);
    }

    void ShaderGL::SetInt2(const char* uniName, const glm::ivec2& vec) const {
        glUniform2i(GetUniformLocation(uniName), vec.x, vec.y);
    }

    void ShaderGL::SetInt3(const char* uniName, const glm::ivec3& vec) const {
        glUniform3i(GetUniformLocation(uniName), vec.x, vec.y, vec.z);
    }

    void ShaderGL::SetInt4(const char* uniName, const glm::ivec4& vec) const {
        glUniform4i(GetUniformLocation(uniName), vec.x, vec.y, vec.z, vec.w);
    }

    void ShaderGL::SetIntVector(const char* uniName, const i32* data, i32 count) const {
        glUniform1iv((GLint)GetUniformLocation(uniName), count, data);
    }

    void ShaderGL::SetMat2(const char* uniName, const glm::mat2& mat) const {
        glUniformMatrix2fv((GLint)GetUniformLocation(uniName), 1, GL_FALSE, glm::value_ptr(mat));
    }

    void ShaderGL::SetMat3(const char* uniName, const glm::mat3& mat) const {
        glUniformMatrix3fv((GLint)GetUniformLocation(uniName), 1, GL_FALSE, glm::value_ptr(mat));
    }

    void ShaderGL::SetMat4(const char* uniName, const glm::mat4& mat) const {
        glUniformMatrix4fv((GLint)GetUniformLocation(uniName), 1, GL_FALSE, glm::value_ptr(mat));
    }

    ShaderGL::~ShaderGL() {
        for (const auto& [_, id] : m_shadersId) {
            glDeleteShader(id);
        }
        glDeleteProgram(m_programId);
    }

    // TODO: Move this funciton into something like `AShadersCompiler::Compile()`
    GlID ShaderGL::CompileShader(EShaderStage stage, StringView source) const {
        RUBY_ASSERT(stage != EShaderStage::SHADER_PROGRAM && stage != EShaderStage::NONE,
            "Either EShaderStage::SHADER_PROGRAM or EShaderStage::NONE passed here"
        );

        // TODO: Replace std::hash with more stable hash function
        auto hashedShaderSource = IntCast::ToString(std::hash<StringView>{}(source)).value_or("");
        if (hashedShaderSource.empty()) {
            RUBY_ERROR("ShaderGL::CompileShader() : Failed to cast integer hash of the shader source into the string");
            return RUBY_GL_UNDEFINED_ID;
        }

        if (auto shaderCacheEntry = TryToGetCachedShader(hashedShaderSource); shaderCacheEntry) {
            return CreateFromSpirVByteCode(stage, "main", shaderCacheEntry.value().spriVByteCode);
        }


        auto outputFilePath = ShaderCacheManager::GetInstance().GetCacheDirAbsolutePath() / hashedShaderSource;

        SpirV::CompilationDetails cDetails;
        cDetails.stage = stage;
        cDetails.src = source;
        cDetails.enviroment = ESpirVEnviroment::OpenGL;
        cDetails.optimizationLevel = ESpirVOptimizationLevel::PERFORMANCE;
        cDetails.outputFile = outputFilePath.string();

        Vector<u32> byteCode = SpirV::CompileGLSL(cDetails).value_or(Vector<u32>{});
        GlID id = CreateFromSpirVByteCode(stage, "main", byteCode);
        if (id == RUBY_GL_UNDEFINED_ID) {
            return RUBY_GL_UNDEFINED_ID;
        }

        auto& manager = ShaderCacheManager::GetInstance();
        if (!manager.AddToCache(hashedShaderSource, ShaderCacheEntry{byteCode})) RUBY_UNLIKELY {
            RUBY_WARNING("ShaderGL::CompileShader() : Failed to add {} in to the local or global cache!",
                hashedShaderSource
            );
        }

        return id;
    }

    // I suppose, this function also should be moved somewhere else
    GlID ShaderGL::CreateFromSpirVByteCode(EShaderStage stage, StringView entry, const Vector<u32>& byteCode) const {
        if (byteCode.empty()) {
            return RUBY_GL_UNDEFINED_ID;
        }

        GlID id = glCreateShader(Cast<EShaderStage>::ToGLenum(stage).value_or(RUBY_GL_UNDEFINED_ID));

        glShaderBinary(1, &id,
                       GL_SHADER_BINARY_FORMAT_SPIR_V, byteCode.data(),
                       BasicCast::To<GLsizei>(byteCode.size() * sizeof(u32))
        );
        glSpecializeShader(id, entry.data(), 0, nullptr, nullptr);


        if (hasShaderProcessError(id, stage)) {
            return RUBY_GL_UNDEFINED_ID;
        }

        return id;
    }
}
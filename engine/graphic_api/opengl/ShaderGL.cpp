#include "ShaderGL.hpp"

#include <utility/Algorithm.hpp>
#include <utility/Assert.hpp>
#include <utility/Cast.hpp>
#include <types/Logger.hpp>
#include <types/File.hpp>
#include <renderer/SpirV.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>



namespace {
    bool hasShaderProcessError(GLuint target, Ruby::ShaderStage type) {
        using namespace Ruby;

        GLint hasNoErrors = 0;
        bool isProgramReceived = (type == ShaderStage::SHADER_PROGRAM);

        switch (isProgramReceived) {
            case true: 
                glGetProgramiv(target, GL_LINK_STATUS, &hasNoErrors); 
                break;
            case false: 
                glGetShaderiv(target, GL_COMPILE_STATUS, &hasNoErrors);
                break;
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

    GLenum rubyShaderStageToGLenum(Ruby::ShaderStage stage) {
        using namespace Ruby;

        switch (stage) {
            case ShaderStage::VERTEX:
                return GL_VERTEX_SHADER;
            case ShaderStage::TESS_CONTROL:
                return GL_TESS_CONTROL_SHADER;
            case ShaderStage::TESS_EVALUATION:
                return GL_TESS_EVALUATION_SHADER;
            case ShaderStage::GEOMETRY:
                return GL_GEOMETRY_SHADER;
            case ShaderStage::FRAGMENT:
                return GL_FRAGMENT_SHADER;
            case ShaderStage::COMPUTE:
                return GL_COMPUTE_SHADER;
            default:
                RUBY_ERROR("rubyShaderStageToGLenum() : Unknown stage received");
                return RUBY_GL_UNDEFINED_ID;
        }
    }

    std::filesystem::path getSpirVCacheDirectory() {
        static auto path = std::filesystem::current_path() / "spirv_cache";

        return path;
    }
}


namespace Ruby::OpenGL {
    const void* ShaderGL::GetNativeProgramHandle() const {
        return &m_programId;
    }

    const void* ShaderGL::GetNativeShaderHandle(ShaderStage stage) const {
        if (!m_shadersId.contains(stage)) {
            return nullptr;
        }
        return &m_shadersId.at(stage);
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

    void ShaderGL::AddShader(ShaderStage stage, const String& path, bool overrideExistingStage) {
        if (m_sourcesToCompile == nullptr) {
            m_sourcesToCompile = new UncompiledSourcesMap();
        }

        if (overrideExistingStage) {
            m_sourcesToCompile->emplace(stage, path);
        }
        else {
            m_sourcesToCompile->try_emplace(stage, path);
        }
    }

    void ShaderGL::AddShader(const String& src, bool overrideExistingStage) {
        auto optSplittedSource = SplitUnifiedShaderSource(src);
        if (!optSplittedSource) {
            return;
        }

        for (const auto& [stage, stageSource] : optSplittedSource.value()) {
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
        for (const auto& [type, src] : *m_sourcesToCompile) {
            GlID id = CompileShader(type, src.data());
            if (id == RUBY_GL_UNDEFINED_ID) {
                completedWithoutErrors = false;
                continue;
            }

            m_shadersId[type] = id;
            glAttachShader(m_programId, id);
        }

        delete m_sourcesToCompile;
        if (!completedWithoutErrors) {
            return;
        }

        glLinkProgram(m_programId);
        if (hasShaderProcessError(m_programId, ShaderStage::SHADER_PROGRAM)) {
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

    GlID ShaderGL::CompileShader(ShaderStage stage, const char* source) const {
        RUBY_ASSERT(stage == ShaderStage::SHADER_PROGRAM && stage == ShaderStage::NONE,
                    "ShaderGL::CompileShader() : Either ShaderStage::SHADER_PROGRAM or ShaderStage::NONE passed here"
        );

        
        SpirV::CompilationDetails cDetails;
        cDetails.enviroment = SpirVEnviroment::OpenGL;
        cDetails.optimizationLevel = SpirVOptimizationLevel::PERFORMANCE;
        cDetails.stage = stage;
        cDetails.src = source;
        cDetails.outputFile = "";

        auto byteCode = SpirV::CompileGLSL(cDetails);
        if (!byteCode) {
            return RUBY_GL_UNDEFINED_ID;
        }

        GlID id = glCreateShader(rubyShaderStageToGLenum(stage));
        
        glShaderBinary(1, &id, GL_SHADER_BINARY_FORMAT_SPIR_V,
                       byteCode.value().data(), static_cast<GLsizei>(byteCode.value().size())
        );
        glSpecializeShader(id, "main", 0, nullptr, nullptr);


        if (hasShaderProcessError(id, stage)) {
            return RUBY_GL_UNDEFINED_ID;
        }
        
        return id;
    }
}
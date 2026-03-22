#include "ShaderGL.hpp"

#include <utility/Algorithm.hpp>
#include <utility/Assert.hpp>

#include <common/cast/Cast.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>


namespace Kiwi::OpenGL {
    ShaderGL::ShaderGL(GlID programId, HashMap<EShaderStage, GlID>&& shaderModules) :
        m_programId(programId),
        m_shaderModulesId(std::move(shaderModules))
    {}
    
    void* ShaderGL::GetNativePipelineHandle() {
        return &m_programId;
    }

    const void* ShaderGL::GetNativePipelineHandle() const {
        return GetNativePipelineHandle();
    }

    void* ShaderGL::GetNativeShaderModuleHandle(EShaderStage stage) {
        if (!m_shaderModulesId.contains(stage)) {
            return nullptr;
        }
        return &m_shaderModulesId.at(stage);
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

    bool ShaderGL::IsEmpty() const {
        return m_shaderModulesId.empty() && m_programId == KIWI_GL_UNDEFINED_ID;
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
        for (const auto& [_, id] : m_shaderModulesId) {
            glDeleteShader(id);
        }
        glDeleteProgram(m_programId);
    }
}
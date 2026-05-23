#include "ShaderGL.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>


namespace Kiwi::OpenGL {
    ShaderGL::ShaderGL(GlID programId, Map<EShaderStage, ShaderModuleGL>&& shaderModules) :
        Super(std::move(shaderModules)),
        m_programId(programId)
    {}
    
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
        return m_shaderModules.empty() && m_programId == KIWI_GL_UNDEFINED_ID;
    }

    void ShaderGL::SetFloat(const char* uniform, f32 value) const {
        glUniform1f(GetUniformLocation(uniform), value);
    }

    void ShaderGL::SetFloat2(const char* uniform, const glm::vec2& vec) const {
        glUniform2f(GetUniformLocation(uniform), vec.x, vec.y);
    }

    void ShaderGL::SetFloat3(const char* uniform, const glm::vec3& vec) const {
        glUniform3f(GetUniformLocation(uniform), vec.x, vec.y, vec.z);
    }

    void ShaderGL::SetFloat4(const char* uniform, const glm::vec4& vec) const {
        glUniform4f(GetUniformLocation(uniform), vec.x, vec.y, vec.z, vec.w);
    }

    void ShaderGL::SetFloatVector(const char* uniform, const f32* data, i32 count) const {
        glUniform1fv(GetUniformLocation(uniform), count, data);
    }

    void ShaderGL::SetInt(const char* uniform, i32 value) const {
        glUniform1i(GetUniformLocation(uniform), value);
    }

    void ShaderGL::SetInt2(const char* uniform, const glm::ivec2& vec) const {
        glUniform2i(GetUniformLocation(uniform), vec.x, vec.y);
    }

    void ShaderGL::SetInt3(const char* uniform, const glm::ivec3& vec) const {
        glUniform3i(GetUniformLocation(uniform), vec.x, vec.y, vec.z);
    }

    void ShaderGL::SetInt4(const char* uniform, const glm::ivec4& vec) const {
        glUniform4i(GetUniformLocation(uniform), vec.x, vec.y, vec.z, vec.w);
    }

    void ShaderGL::SetIntVector(const char* uniform, const i32* data, i32 count) const {
        glUniform1iv((GLint)GetUniformLocation(uniform), count, data);
    }

    void ShaderGL::SetMat2(const char* uniform, const glm::mat2& mat) const {
        glUniformMatrix2fv((GLint)GetUniformLocation(uniform), 1, GL_FALSE, glm::value_ptr(mat));
    }

    void ShaderGL::SetMat3(const char* uniform, const glm::mat3& mat) const {
        glUniformMatrix3fv((GLint)GetUniformLocation(uniform), 1, GL_FALSE, glm::value_ptr(mat));
    }

    void ShaderGL::SetMat4(const char* uniform, const glm::mat4& mat) const {
        glUniformMatrix4fv((GLint)GetUniformLocation(uniform), 1, GL_FALSE, glm::value_ptr(mat));
    }

    ShaderGL::~ShaderGL() {
        for (const UniquePtr<IShaderModule>& id : std::views::values(m_shaderModules)) {
            auto* nativeId = CastTo<const GlID*>(id->GetNativeHandle());
            glDeleteShader(*nativeId);
        }
        glDeleteProgram(m_programId);
    }
}
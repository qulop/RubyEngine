#include "GlShader.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>


namespace Ruby
{
    static void getShaderProcessError(GLuint target, bool isProgram=false)
    {
        GLint isAllGood;
        GLchar buffer[512];

        if (isProgram)
            glGetProgramiv(target, GL_LINK_STATUS, &isAllGood);
        else
            glGetShaderiv(target, GL_COMPILE_STATUS, &isAllGood);

        if (isAllGood)
            return;

        auto errorTarget = (isProgram) ? "linking" : "compiling";
        auto bufferSize = static_cast<GLsizei>(std::size(buffer));

        if (isProgram)
            glGetProgramInfoLog(target, bufferSize, nullptr, buffer);
        else
            glGetShaderInfoLog(target, bufferSize, nullptr, buffer);

        RUBY_ERROR("An error occured while {} shader: {}", errorTarget, buffer);
    }


    static GLenum getGlShaderType(ShaderTypes type)
    {
        switch (type)
        {
            case RUBY_VERTEX_SHADER: return GL_VERTEX_SHADER;
            case RUBY_FRAGMENT_SHADER: return GL_FRAGMENT_SHADER;
            default: RUBY_WRECK("getGlShaderType() : Unknown shader type!");
        }
    }


    GlShader::GlShader(const RubyString& vertexSrc, const RubyString& fragmentSrc)
    {
        m_sources[RUBY_VERTEX_SHADER] = vertexSrc;
        m_sources[RUBY_FRAGMENT_SHADER] = fragmentSrc;
    }

    RubyString GlShader::GetSource(ShaderTypes type) const
    { return m_sources.at(type); }

    u32 GlShader::GetShaderID(ShaderTypes type) const
    { return m_shadersId.at(type); }


    u32 GlShader::GetProgramID() const
    { return m_programId; }

    u32 GlShader::GetUniformLocation(cstr name) const
    {  return glGetUniformLocation(m_programId, name); }

    void GlShader::Bind()
    { glUseProgram(m_programId); }

    void GlShader::Unbind()
    { glUseProgram(0); }

    void GlShader::AddSource(ShaderTypes type, const RubyString& src)
    { m_sources[type] = src; }

    bool GlShader::IsEmpty() const
    { return m_sources.size() == 0; }

    bool GlShader::IsReady() const
    { return m_isReady; }

    void GlShader::Compile()
    {
        for (const auto& shader: m_sources)
        {
            auto type = shader.first;
            auto source = shader.second.c_str();

            m_shadersId[type] = CompileShader(type, source);
        }

        m_programId = glCreateProgram();
        for (const auto& id : m_shadersId)
            glAttachShader(m_programId, id.second);
        glLinkProgram(m_programId);

        getShaderProcessError(m_programId, true);

        RUBY_SWITCH_BOOL(m_isReady);
    }

    void GlShader::SetFloat(cstr uniName, f32 value)
    {
        glm::vec1 tmp{ value };
        SetTypeN<1, f32>(uniName, tmp);
    }

    void GlShader::SetFloat2(cstr uniName, const glm::vec2& vec)
    { SetTypeN<2, f32>(uniName, vec); }

    void GlShader::SetFloat3(cstr uniName, const glm::vec3& vec)
    { SetTypeN<3, f32>(uniName, vec); }

    void GlShader::SetFloat4(cstr uniName, const glm::vec4& vec)
    { SetTypeN<4, f32>(uniName, vec); }

    void GlShader::SetFloatVector(cstr uniName, const f32* data, i32 count)
    {
        auto loc = GetUniformLocation(uniName);
        glUniform1fv(loc, count, data);
    }


    void GlShader::SetInt(cstr uniName, i32 value)
    {
        glm::ivec1 tmp{ value };
        SetTypeN<1, i32>(uniName, tmp);
    }

    void GlShader::SetInt2(cstr uniName, const glm::ivec2& vec)
    { SetTypeN<2, i32>(uniName, vec); }

    void GlShader::SetInt3(cstr uniName, const glm::ivec3& vec)
    { SetTypeN<3, i32>(uniName, vec); }


    void GlShader::SetInt4(cstr uniName, const glm::ivec4& vec)
    { SetTypeN<4, i32>(uniName, vec); }

    void GlShader::SetIntVector(cstr uniName, const i32* data, i32 count)
    {
        auto loc = GetUniformLocation(uniName);
        glUniform1iv(loc, count, data);
    }


    void GlShader::SetMat4(cstr uniName, const glm::mat4& mat)
    {
        auto loc = GetUniformLocation(uniName);
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
    }


    void SetFloatV(cstr uniName, const f32* data, i32 count);
    void SetInt(cstr uniName, i32 value);
    void SetIntV(cstr uniName, const i32* data, i32 count);
    void SetMat4(cstr uniName, const glm::mat4& mat);



    u32 GlShader::CompileShader(ShaderTypes type, cstr source)
    {
        u32 id = glCreateShader(getGlShaderType(type));
        glShaderSource(id, 1, &source, nullptr);
        glCompileShader(id);

        getShaderProcessError(id);

        return id;
    }
}
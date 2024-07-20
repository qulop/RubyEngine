#include "Shader.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>


namespace Ruby
{
    // ------ UTILS -----
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

        RUBY_ERROR("An error occurred while {} shader: {}", errorTarget, buffer);
    }


    static GLenum getShaderType(ShaderTypes type)
    {
        switch (type)
        {
            case RUBY_VERTEX_SHADER: return GL_VERTEX_SHADER;
            case RUBY_FRAGMENT_SHADER: return GL_FRAGMENT_SHADER;
            default: RUBY_WRECK("getShaderType() : Unknown shader type!");
        }
    }

    template<size_t N, typename Type>
    void setUniformForType(cstr uniName, u32 loc, const glm::vec<N, Type, glm::defaultp>& vec)
    {
        #ifdef RUBY_MSVC_USED
            #pragma warning(push)
            #pragma warning(disable : 4244)
        #endif
        static_assert((N >= 1 && N <= 4) && (std::is_floating_point_v<Type> || std::is_integral_v<Type>));

        constexpr bool isInt = std::is_integral_v<Type>;
        if constexpr (isInt)
        {
            if constexpr (N == 1)
                glUniform1i(loc, vec.x);
            else if constexpr (N == 2)
                glUniform2i(loc, vec.x, vec.y);
            else if constexpr (N == 3)
                glUniform3i(loc, vec.x, vec.y, vec.z);
            else
                glUniform4i(loc, vec.x, vec.y, vec.z, vec.w);
            return;
        }

        if constexpr (N == 1)
            glUniform1f(loc, vec.x);
        else if constexpr (N == 2)
            glUniform2f(loc, vec.x, vec.y);
        else if constexpr (N == 3)
            glUniform3f(loc, vec.x, vec.y, vec.z);
        else
            glUniform4f(loc, vec.x, vec.y, vec.z, vec.w);

        #ifdef RUBY_MSVC_USED
            #pragma warning(pop)
        #endif
    }
    // ----------------




    Shader::Shader(const RubyString& vertexSrc, const RubyString& fragmentSrc)
    {
        m_sources[RUBY_VERTEX_SHADER] = vertexSrc;
        m_sources[RUBY_FRAGMENT_SHADER] = fragmentSrc;
    }


    RubyString Shader::GetSource(ShaderTypes type) const
    { return m_sources.at(type); }


    u32 Shader::GetShaderID(ShaderTypes type) const
    { return m_shadersId.at(type); }


    u32 Shader::GetProgramID() const
    { return m_programId; }


    u32 Shader::GetUniformLocation(cstr name) const
    {  return glGetUniformLocation(m_programId, name); }


    void Shader::Bind()
    { glUseProgram(m_programId); }


    void Shader::Unbind()
    { glUseProgram(0); }


    void Shader::AddSource(ShaderTypes type, const RubyString& src)
    { m_sources[type] = src; }


    bool Shader::IsEmpty() const
    { return m_sources.empty(); }


    bool Shader::IsReady() const
    { return m_isReady; }


    void Shader::Compile()
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


    void Shader::SetFloat(cstr uniName, f32 value) const
    {
        glm::vec1 tmp{ value };
        setUniformForType<1, f32>(uniName, GetUniformLocation(uniName), tmp);
    }


    void Shader::SetFloat2(cstr uniName, const glm::vec2& vec) const
    { setUniformForType<2, f32>(uniName, GetUniformLocation(uniName), vec); }


    void Shader::SetFloat3(cstr uniName, const glm::vec3& vec) const
    { setUniformForType<3, f32>(uniName, GetUniformLocation(uniName), vec); }


    void Shader::SetFloat4(cstr uniName, const glm::vec4& vec) const
    { setUniformForType<4, f32>(uniName, GetUniformLocation(uniName), vec); }


    void Shader::SetFloatVector(cstr uniName, const f32* data, i32 count) const
    {
        auto loc = GetUniformLocation(uniName);
        glUniform1fv(loc, count, data);
    }


    void Shader::SetInt(cstr uniName, i32 value) const
    {
        glm::ivec1 tmp{ value };
        setUniformForType<1, i32>(uniName, GetUniformLocation(uniName), tmp);
    }


    void Shader::SetInt2(cstr uniName, const glm::ivec2& vec) const
    { setUniformForType<2, i32>(uniName, GetUniformLocation(uniName), vec); }


    void Shader::SetInt3(cstr uniName, const glm::ivec3& vec) const
    { setUniformForType<3, i32>(uniName, GetUniformLocation(uniName), vec); }


    void Shader::SetInt4(cstr uniName, const glm::ivec4& vec) const
    { setUniformForType<4, i32>(uniName, GetUniformLocation(uniName), vec); }


    void Shader::SetIntVector(cstr uniName, const i32* data, i32 count) const
    {
        auto loc = GetUniformLocation(uniName);
        glUniform1iv(loc, count, data);
    }


    void Shader::SetMat4(cstr uniName, const glm::mat4& mat) const
    {
        auto loc = GetUniformLocation(uniName);
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
    }



    u32 Shader::CompileShader(ShaderTypes type, cstr source)
    {
        u32 id = glCreateShader(getShaderType(type));
        glShaderSource(id, 1, &source, nullptr);
        glCompileShader(id);

        getShaderProcessError(id);

        return id;
    }
}
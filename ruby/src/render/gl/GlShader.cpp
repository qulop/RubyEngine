#include <render/gl/GlShader.hpp>


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
        if (isProgram)
            glGetProgramInfoLog(target, std::size(buffer), nullptr, buffer);
        else
            glGetShaderInfoLog(target, std::size(buffer), nullptr, buffer);

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

    std::optional<RubyString> GlShader::GetSource(ShaderTypes type) const
    {
        if (m_sources.find(type) == m_sources.end())
            return std::nullopt;
        return m_sources.at(type);
    }

    std::optional<u32> GlShader::GetShaderID(ShaderTypes type) const
    {
        if (!m_isReady)
            return std::nullopt;
        return m_shadersId.at(type);
    }


    std::optional<u32> GlShader::GetProgramID() const
    {
        if (!m_isReady)
            return std::nullopt;
        return m_programId;
    }

    std::optional<u32> GlShader::GetUniformLocation(cstr name) const
    {
        if (!m_isReady)
            return std::nullopt;
        return glGetUniformLocation(m_programId, name);
    }

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


    u32 GlShader::CompileShader(ShaderTypes type, cstr source)
    {
        u32 id = glCreateShader(getGlShaderType(type));
        glShaderSource(id, 1, &source, nullptr);
        glCompileShader(id);

        getShaderProcessError(id);

        return id;
    }
}
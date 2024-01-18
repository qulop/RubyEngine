#include "Shader.hpp"


namespace Ruby
{
    void GetShaderProcessError(GLuint target, bool isProgram)
    {
        GLint isAllGood;
        GLchar buffer[512];

        if (isProgram)
            glGetProgramiv(target, GL_LINK_STATUS, &isAllGood);
        else
            glGetShaderiv(target, GL_COMPILE_STATUS, &isAllGood);

        if (isAllGood)
            return;

        const char* errorTarget = (isProgram) ? "linking" : "compiling";
        if (isProgram)
            glGetProgramInfoLog(target, sizeof(buffer) / sizeof(GLchar), nullptr, buffer);
        else
            glGetShaderInfoLog(target, sizeof(buffer) / sizeof(GLchar), nullptr, buffer);

        RUBY_ERROR("An error occured while {} shader: {}", errorTarget, buffer);
    }


    Shader::Shader(const RubyString& path, GLenum type)
    {
        std::ifstream file(path, std::ios_base::in);
        if (!file.is_open())
        {
            RUBY_ERROR("Failed to load shader: cannot open file {} (!file.is_open())", path);
            return;
        }

        RubyString line;
        while (file.good())
        {
            std::getline(file, line);
            m_source.append(line.c_str());
        }

        m_type = type;
    }


    void Shader::ShaderSource(const RubyString& src, GLenum type)
    {
        m_source = src;
        m_type = type;
    }


    void Shader::Compile(void)
    {
        auto cStyleSrc = m_source.c_str();

        GLuint shader = glCreateShader(m_type);
        glShaderSource(shader, 1, &cStyleSrc, nullptr);
        glCompileShader(shader);

        GetShaderProcessError(shader);
    }


    const RubyString& Shader::GetSource(void) const
    {
        return m_source.size() ? m_source : nullptr;
    }


    GLenum Shader::GetType(void) const
    { return m_type; }


    GLuint Shader::GetShaderID(void) const
    {
        RUBY_ASSERT(m_shader != static_cast<GLuint>(-1) && "The shader must first be compiled: use Shader::Compile()");

        return m_shader; 
    }
}
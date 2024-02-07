#include "ShaderProgram.hpp"


namespace Ruby
{
    ShaderProgram::ShaderProgram(const RubyString& configPath)
    {
        Json configFile = Json::parse(
            std::ifstream{ configPath, std::ios_base::in });
        
        auto appliedShaders = configFile["appliedShaders"];
        // if (appliedShaders.empty())
        // {
        //     RUBY_CRITICAL("Cannot load shaders from path {}: Config.json is corrupted.")
        // }

        for (auto i : appliedShaders.at("vertex"))
        {
            m_shadersList.emplace_back(i, GL_VERTEX_SHADER);
            RUBY_INFO("GL_VERTEX_SHADER: {}", i);
        }

        for (auto i : appliedShaders.at("fragment"))
        {
            m_shadersList.emplace_back(i, GL_FRAGMENT_SHADER);
            RUBY_INFO("GL_FRAGMENT_SHADER: {}", i);
        }

    }


    void ShaderProgram::AddShader(const Shader& shader)
    {
        m_shadersList.push_back(shader);
    }


    void ShaderProgram::AddShader(Shader&& shader)
    {
        m_shadersList.push_back(std::move(shader));
    }


    void ShaderProgram::CreateProgram(void)
    {
        for (auto& shader : m_shadersList)
            shader.Compile();

        m_shaderProgram = glCreateProgram();

        for (const auto& shader : m_shadersList)
            glAttachShader(m_shaderProgram, shader.GetShaderID());
        glLinkProgram(m_shaderProgram);

        GetShaderProcessError(m_shaderProgram, true);
    }


    void ShaderProgram::UseProgram(void)
    {
        RUBY_ASSERT(m_shaderProgram != static_cast<GLuint>(-1) 
            && "You should firstly create program(ShaderProgram::CreateProgram()), before use it.");

        glUseProgram(m_shaderProgram);
    }


    GLuint ShaderProgram::GetUniformLocation(const RubyString& name)
    {
        RUBY_ASSERT(m_shaderProgram != static_cast<GLuint>(-1) 
            && "You should firstly create program(ShaderProgram::CreateProgram()), before as getting uniform location.");
                 
        return glGetUniformLocation(m_shaderProgram, name.c_str()); 
    }


    GLuint ShaderProgram::GetProgramID(void) const
    {
        RUBY_ASSERT(m_shaderProgram != static_cast<GLuint>(-1) 
            && "You must create shader program before as getting it's ID");

        return m_shaderProgram;
    }

}

#include "ShadersManager.hpp"


namespace Ruby
{
    ShadersManager::ShadersManager(const RubyString& configPath)
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


    void ShadersManager::AddShader(Shader&& shader)
    {
        m_shadersList.emplace_back(std::forward<Shader>(shader));
    }


    void ShadersManager::CreateProgram(void)
    {
        for (auto& shader : m_shadersList)
            shader.Compile();

        m_shaderProgram = glCreateProgram();

        for (const auto& shader : m_shadersList)
            glAttachShader(m_shaderProgram, shader.GetShaderID());
        glLinkProgram(m_shaderProgram);

        GetShaderProcessError(m_shaderProgram, true);
    }


    void ShadersManager::UseProgram(void)
    {
        glUseProgram(m_shaderProgram);
    }


    GLuint ShadersManager::GetProgramID(void) const
    {
        RUBY_ASSERT(m_shaderProgram != static_cast<GLuint>(-1) && "You must create shader program before as getting it's ID");

        return m_shaderProgram;
    }
}

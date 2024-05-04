#include <render/ShaderProgram.hpp>


namespace Ruby 
{
    ShaderProgram::ShaderProgram(const RubyString& configPath) 
	{
        Json configFile = Json::parse(
                std::ifstream{configPath, std::ios_base::in});

        auto appliedShaders = configFile["appliedShaders"];
        if (appliedShaders.empty()) 
		{
            RUBY_CRITICAL("Cannot load shaders from path {}: Config.json is corrupted.", configPath);
            return;
        }

        for (auto i: appliedShaders.at("vertex")) 
		{
            m_shadersList.emplace_back(i, GL_VERTEX_SHADER);
            RUBY_INFO("GL_VERTEX_SHADER: {}", i);
        }

        for (auto i: appliedShaders.at("fragment")) 
		{
            m_shadersList.emplace_back(i, GL_FRAGMENT_SHADER);
            RUBY_INFO("GL_FRAGMENT_SHADER: {}", i);
        }

    }


    ShaderProgram& ShaderProgram::AddShader(const Shader& shader) 
	{
        m_shadersList.push_back(shader);

        return *this;
    }


    ShaderProgram &ShaderProgram::AddShader(Shader&& shader) 
	{
        m_shadersList.push_back(std::move(shader));

        return *this;
    }


    void ShaderProgram::CreateProgram() 
	{
        for (auto& shader: m_shadersList)
            shader.Compile();

        m_shaderProgram = glCreateProgram();

        for (const auto &shader: m_shadersList)
            glAttachShader(m_shaderProgram, shader.GetShaderID());
        glLinkProgram(m_shaderProgram);

        GetShaderProcessError(m_shaderProgram, true);
    }


    void ShaderProgram::UseProgram() const 
	{
        RUBY_ASSERT(m_shaderProgram != static_cast<GLuint>(-1),
                    "You should firstly create program(ShaderProgram::CreateProgram()), before use it.");

        glUseProgram(m_shaderProgram);
    }


    GLuint ShaderProgram::GetUniformLocation(const RubyString& name) const 
	{
        RUBY_ASSERT(m_shaderProgram != static_cast<GLuint>(-1),
                    "You should firstly create program(ShaderProgram::CreateProgram()), before as getting uniform location.");

        return glGetUniformLocation(m_shaderProgram, name.c_str());
    }


    GLuint ShaderProgram::GetProgramID() const 
	{
        RUBY_ASSERT(m_shaderProgram != static_cast<GLuint>(-1),
                    "You must create shader program before as getting it's ID");

        return m_shaderProgram;
    }


    ShaderProgram& ShaderProgram::operator=(const ShaderProgram& other) 
	{
        if (*this == other)
            return *this;

        m_shadersList = other.m_shadersList;
        m_shaderProgram = other.m_shaderProgram;

        return *this;
    }


    ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) 
	{
        if (*this == other)
            return *this;

        m_shadersList = std::move(other.m_shadersList);
        m_shaderProgram = other.m_shaderProgram;

        return *this;
    }

    bool ShaderProgram::operator==(const ShaderProgram& other) const
    { return (m_shaderProgram == other.m_shaderProgram); }

    bool ShaderProgram::operator!=(const ShaderProgram& other) const
    { return !(*this == other); }
}

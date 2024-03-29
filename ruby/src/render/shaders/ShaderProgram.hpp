#pragma once

#include <nlohmann/json.hpp>

#include "Shader.hpp"
#include "Uniform.hpp"

#include <initializer_list>
#include <fstream>
#include <vector>


namespace Ruby
{
    class ShaderProgram
    {
    public:
        using Json = nlohmann::json;

        ShaderProgram(void) = default;

        ShaderProgram(const RubyString& configPath);

        ShaderProgram(std::initializer_list<Shader>&& il) :
            m_shadersList(il) {}

        void AddShader(const Shader& shader);

        void AddShader(Shader&& shader);

        template<typename... Args>
        void EmplaceShader(Args&&... args)
        {
            m_shadersList.emplace_back(std::forward<Args>(args)...);
        }

        void CreateProgram(void);

        GLuint GetUniformLocation(const RubyString& name);

        void UseProgram(void);

        GLuint GetProgramID(void) const;

    private:
        RubyVector<Shader> m_shadersList;
        GLuint m_shaderProgram = -1;
    };
}
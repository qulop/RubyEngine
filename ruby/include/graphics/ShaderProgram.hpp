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

        ShaderProgram() = default;

        ShaderProgram(const RubyString& configPath);

        ShaderProgram(std::initializer_list<Shader>&& il) :
            m_shadersList(il) {}

        ShaderProgram& AddShader(const Shader& shader);

        ShaderProgram& AddShader(Shader&& shader);

        template<typename... Args>
        ShaderProgram& EmplaceShader(Args&&... args)
        {
            m_shadersList.emplace_back(std::forward<Args>(args)...);

            return *this;
        }

        void CreateProgram();

        GLuint GetUniformLocation(const RubyString& name) const;

        void UseProgram() const;

        GLuint GetProgramID() const;

    private:
        RubyVector<Shader> m_shadersList;
        GLuint m_shaderProgram = -1;
    };
}
#pragma once

#include <nlohmann/json.hpp>

#include "Shader.hpp"
#include "Uniform.hpp"

#include <utility/StdInc.hpp>


namespace Ruby
{
    class ShaderProgram
    {
        using Json = nlohmann::json;
    public:

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

        RUBY_NODISCARD GLuint GetUniformLocation(const RubyString& name) const;

        void UseProgram() const;

        RUBY_NODISCARD GLuint GetProgramID() const;

        ShaderProgram& operator=(const ShaderProgram& other);
        ShaderProgram& operator=(ShaderProgram&& other);
        bool operator==(const ShaderProgram& other) const;
        bool operator!=(const ShaderProgram& other) const;

    private:
        RubyVector<Shader> m_shadersList;
        GLuint m_shaderProgram = -1;
    };
}
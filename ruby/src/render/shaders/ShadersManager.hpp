#pragma once

#include <nlohmann/json.hpp>

#include "Shader.hpp"

#include <initializer_list>
#include <fstream>
#include <vector>


namespace Ruby
{
    class ShadersManager
    {
    public:
        using Json = nlohmann::json;

        ShadersManager(void) = default;

        ShadersManager(const RubyString& configPath);

        ShadersManager(std::initializer_list<Shader>&& il) :
            m_shadersList(il) {}

        void AddShader(Shader&& shader);

        template<typename... Args>
        void EmplaceShader(Args&&... args)
        {
            m_shadersList.emplace_back(std::forward<Args>(args)...);
        }

        void CreateProgram(void);

        void UseProgram(void);

        GLuint GetProgramID(void) const;

    private:
        RubyVector<Shader> m_shadersList;
        GLuint m_shaderProgram = -1;
    };
}
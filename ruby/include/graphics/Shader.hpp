#pragma once

#include <utility/Definitions.hpp>
#include <utility/Logger.hpp>
#include <glad/glad.h>

#include <fstream>
#include <expected>
#include <optional>

namespace Ruby
{
    void GetShaderProcessError(GLuint target, bool isProgram = false);


    class Shader
    {
    public:
        Shader() = default;

        Shader(const RubyString& path, GLenum type);

        void ShaderSource(const RubyString& src, GLenum type);

        void Compile();

        std::expected<RubyStringView, cstr> GetSource() const;

        GLenum GetType() const;

        GLuint GetShaderID() const;

    private:
        RubyString m_source;
        GLenum m_type = -1;
        GLuint m_shader = -1;
    };
}
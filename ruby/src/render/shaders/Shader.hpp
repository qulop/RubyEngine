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
        Shader(void) = default;

        Shader(const RubyString& path, GLenum type);

        void ShaderSource(const RubyString& src, GLenum type);

        void Compile(void);

        std::expected<RubyStringView, cstr> GetSource(void) const;

        GLenum GetType(void) const;

        GLuint GetShaderID(void) const;

    private:
        RubyString m_source;
        GLenum m_type = -1;
        GLuint m_shader = -1;
    };
}
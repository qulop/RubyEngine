#pragma once

#include <utility/Definitions.hpp>
#include <utility/Logger.hpp>
#include <glad/glad.h>

#include <fstream>
#include <expected>
#include <optional>

namespace Ruby
{
    enum class ShaderTypes
    {
        NONE,
        INT, IVEC2, IVEC3, IVEC4,
        FLOAT, VEC2, VEC3, VEC4,
        MAT3, MAT4,
        BOOL
    };


    void GetShaderProcessError(GLuint target, bool isProgram = false);

    class Shader
    {
    public:
        Shader() = default;

        Shader(const RubyString& path, GLenum type);

        void ShaderSource(const RubyString& src, GLenum type);

        void Compile();

        RUBY_NODISCARD std::expected<RubyStringView, cstr> GetSource() const;

        RUBY_NODISCARD GLenum GetType() const;

        RUBY_NODISCARD GLuint GetShaderID() const;

    private:
        RubyString m_source;
        GLenum m_type = -1;
        GLuint m_shader = -1;
    };
}
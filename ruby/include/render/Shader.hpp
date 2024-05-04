#pragma once

#include <utility/Definitions.hpp>
#include <utility/Logger.hpp>
#include <utility/StdInc.hpp>

#include <glad/glad.h>


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

        RUBY_NODISCARD std::optional<RubyStringView> GetSource() const;

        RUBY_NODISCARD GLenum GetType() const;

        RUBY_NODISCARD GLuint GetShaderID() const;

    private:
        RubyString m_source;
        GLenum m_type = -1;
        GLuint m_shader = -1;
    };
}
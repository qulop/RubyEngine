#pragma once

#include <utility/RubyUtility.hpp>
#include <utility/StdInc.hpp>

#include <glad/glad.h>


namespace Ruby
{
    RUBY_ENUM(ShaderTypes,
              RUBY_FRAGMENT_SHADER,
              RUBY_VERTEX_SHADER
    );


    abstract class Shader
    {
    public:
        RUBY_NODISCARD virtual std::optional<RubyString> GetSource(ShaderTypes type) const = 0;
        RUBY_NODISCARD virtual std::optional<u32> GetShaderID(ShaderTypes type) const = 0;
        RUBY_NODISCARD virtual std::optional<u32> GetProgramID() const = 0;
        RUBY_NODISCARD virtual std::optional<u32> GetUniformLocation(cstr name) const = 0;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void AddSource(ShaderTypes type, const RubyString& src) = 0;

        RUBY_NODISCARD virtual bool IsEmpty() const = 0;
        RUBY_NODISCARD virtual bool IsReady() const = 0;

        virtual void Compile() = 0;

        virtual ~Shader() = default;

    public:
        static Ptr<Shader> Create();
        static Ptr<Shader> Create(const RubyString& vertexSrc, const RubyString& fragmentSrc);
    };
}
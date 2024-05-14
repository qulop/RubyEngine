#pragma once

#include <render/Shader.hpp>


namespace Ruby
{
    class GlShader : public Shader
    {
    public:
        GlShader() = default;
        GlShader(const RubyString& vertexSrc, const RubyString& fragmentSrc);

        RUBY_NODISCARD std::optional<RubyString> GetSource(ShaderTypes type) const override;
        RUBY_NODISCARD std::optional<u32> GetShaderID(ShaderTypes type) const override;
        RUBY_NODISCARD std::optional<u32> GetProgramID() const override;
        RUBY_NODISCARD std::optional<u32> GetUniformLocation(cstr name) const override;

         void Bind() override;
         void Unbind() override;

         void AddSource(ShaderTypes type, const RubyString& src) override;

        RUBY_NODISCARD bool IsEmpty() const override;
        RUBY_NODISCARD bool IsReady() const override;

         void Compile() override;

         virtual ~GlShader() = default;

    private:
        u32 CompileShader(ShaderTypes type, cstr source);

    private:
        RubyHashMap<ShaderTypes, u32> m_shadersId;
        RubyHashMap<ShaderTypes, RubyString> m_sources;

        u32 m_programId = 0;
        bool m_isReady = false;
    };
}

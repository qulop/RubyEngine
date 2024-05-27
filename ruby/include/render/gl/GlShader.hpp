#pragma once

#include <render/Shader.hpp>

#include <glad/glad.h>


namespace Ruby
{
    namespace Details::Render
    {

    }

    class GlShader : public Shader
    {
    public:
        GlShader(const RubyString& vertexSrc, const RubyString& fragmentSrc);

        RUBY_NODISCARD RubyString GetSource(ShaderTypes type) const override;
        RUBY_NODISCARD u32 GetShaderID(ShaderTypes type) const override;
        RUBY_NODISCARD u32 GetProgramID() const override;
        RUBY_NODISCARD u32 GetUniformLocation(cstr name) const override;

         void Bind() override;
         void Unbind() override;

         void AddSource(ShaderTypes type, const RubyString& src) override;

        RUBY_NODISCARD bool IsEmpty() const override;
        RUBY_NODISCARD bool IsReady() const override;

         void Compile() override;

        void SetFloat(cstr uniName, f32 value) override;
        void SetFloat2(cstr uniName, const glm::vec2& vec) override;
        void SetFloat3(cstr uniName, const glm::vec3& vec) override;
        void SetFloat4(cstr uniName, const glm::vec4& vec) override;
        void SetFloatVector(cstr uniName, const f32* data, i32 count) override;

        void SetInt(cstr uniName, i32 value) override;
        void SetInt2(cstr uniName, const glm::ivec2& vec) override;
        void SetInt3(cstr uniName, const glm::ivec3& vec) override;
        void SetInt4(cstr uniName, const glm::ivec4& vec) override;
        void SetIntVector(cstr uniName, const i32* data, i32 count) override;

        void SetMat4(cstr uniName, const glm::mat4& mat) override;

        virtual ~GlShader() = default;

    private:
        u32 CompileShader(ShaderTypes type, cstr source);

        template<size_t N, typename Type>
        void SetTypeN(cstr uniName, const glm::vec<N, Type, glm::defaultp>& vec)
        {
            static_assert((N >= 1 && N <= 4) && (std::is_floating_point_v<Type> || std::is_integral_v<Type>));

            auto loc = GetUniformLocation(uniName);
            constexpr bool isInt = std::is_integral_v<Type>;

            if constexpr (isInt)
            {
                if constexpr (N == 1)
                    glUniform1i(loc, vec.x);
                else if constexpr (N == 2)
                    glUniform2i(loc, vec.x, vec.y);
                else if constexpr (N == 3)
                    glUniform3i(loc, vec.x, vec.y, vec.z);
                else
                    glUniform4i(loc, vec.x, vec.y, vec.z, vec.w);
                return;
            }

            if constexpr (N == 1)
                glUniform1f(loc, vec.x);
            else if constexpr (N == 2)
                glUniform2f(loc, vec.x, vec.y);
            else if constexpr (N == 3)
                glUniform3f(loc, vec.x, vec.y, vec.z);
            else
                glUniform4f(loc, vec.x, vec.y, vec.z, vec.w);
        }

    private:
        RubyHashMap<ShaderTypes, u32> m_shadersId;
        RubyHashMap<ShaderTypes, RubyString> m_sources;

        u32 m_programId = 0;
        bool m_isReady = false;
    };
}

#pragma once

#include <utility/RubyUtility.hpp>
#include <utility/StdInc.hpp>

#include <glm/glm.hpp>


namespace Ruby
{
    RUBY_ENUM(ShaderTypes,
              RUBY_FRAGMENT_SHADER,
              RUBY_VERTEX_SHADER
    );


    class Shader
    {
    public:
        Shader(const RubyString& vertexSrc, const RubyString& fragmentSrc);

        RUBY_NODISCARD RubyString GetSource(ShaderTypes type) const;
        RUBY_NODISCARD u32 GetShaderID(ShaderTypes type) const;
        RUBY_NODISCARD u32 GetProgramID() const;
        RUBY_NODISCARD u32 GetUniformLocation(cstr name) const;

        void Bind();
        void Unbind();

        void AddSource(ShaderTypes type, const RubyString& src);

        RUBY_NODISCARD bool IsEmpty() const;
        RUBY_NODISCARD bool IsReady() const;

        void Compile();

        void SetFloat(cstr uniName, f32 value) const;
        void SetFloat2(cstr uniName, const glm::vec2& vec) const;
        void SetFloat3(cstr uniName, const glm::vec3& vec) const;
        void SetFloat4(cstr uniName, const glm::vec4& vec) const;
        void SetFloatVector(cstr uniName, const f32* data, i32 count) const;

        void SetInt(cstr uniName, i32 value) const;
        void SetInt2(cstr uniName, const glm::ivec2& vec) const;
        void SetInt3(cstr uniName, const glm::ivec3& vec) const;
        void SetInt4(cstr uniName, const glm::ivec4& vec) const;
        void SetIntVector(cstr uniName, const i32* data, i32 count) const;

        void SetMat4(cstr uniName, const glm::mat4& mat) const;

        ~Shader() = default;

    private:
        u32 CompileShader(ShaderTypes type, cstr source);

    private:
        RubyHashMap<ShaderTypes, u32> m_shadersId;
        RubyHashMap<ShaderTypes, RubyString> m_sources;

        u32 m_programId = 0;
        std::atomic<bool> m_isReady = false;
    };
}
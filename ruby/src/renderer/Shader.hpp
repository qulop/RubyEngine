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


    abstract class Shader
    {
    public:
        RUBY_NODISCARD virtual RubyString GetSource(ShaderTypes type) const = 0;
        RUBY_NODISCARD virtual u32 GetShaderID(ShaderTypes type) const = 0;
        RUBY_NODISCARD virtual u32 GetProgramID() const = 0;
        RUBY_NODISCARD virtual u32 GetUniformLocation(cstr name) const = 0;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void AddSource(ShaderTypes type, const RubyString& src) = 0;

        RUBY_NODISCARD virtual bool IsEmpty() const = 0;
        RUBY_NODISCARD virtual bool IsReady() const = 0;

        virtual void Compile() = 0;

        virtual void SetFloat(cstr uniName, f32 value) = 0;
        virtual void SetFloat2(cstr uniName, const glm::vec2& vec) = 0;
        virtual void SetFloat3(cstr uniName, const glm::vec3& vec) = 0;
        virtual void SetFloat4(cstr uniName, const glm::vec4& vec) = 0;
        virtual void SetFloatVector(cstr uniName, const f32* data, i32 count) = 0;

        virtual void SetInt(cstr uniName, i32 value) = 0;
        virtual void SetInt2(cstr uniName, const glm::ivec2& vec) = 0;
        virtual void SetInt3(cstr uniName, const glm::ivec3& vec) = 0;
        virtual void SetInt4(cstr uniName, const glm::ivec4& vec) = 0;
        virtual void SetIntVector(cstr uniName, const i32* data, i32 count) = 0;

        virtual void SetMat4(cstr uniName, const glm::mat4& mat) = 0;

        virtual ~Shader() = default;

    public:
        static Ptr<Shader> Create();
        static Ptr<Shader> Create(const RubyString& vertexSrc, const RubyString& fragmentSrc);
    };
}
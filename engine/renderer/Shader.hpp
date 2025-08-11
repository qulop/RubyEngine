#pragma once

#include <types/StdInc.hpp>
#include <utility/Definitions.hpp>
#include <utility/Enum.hpp>

#include <glm/glm.hpp>
#include <glad/glad.h>


namespace Ruby {
    enum class ShaderStage : u8 {
        NONE,

        VERTEX, 
        TESS_CONTROL, TESS_EVALUATION,
        GEOMETRY, 
        FRAGMENT,
        COMPUTE,

        SHADER_PROGRAM
    };
    

    class RUBY_API Shader {
    public:
        using UncompiledSourcesMap = HashMap<ShaderStage, String>;

    public:
        RUBY_NODISCARD static Opt<ShaderStage> StringToShaderStage(StringView stageName);

    public:
        RUBY_NODISCARD virtual const void* GetNativeProgramHandle() const = 0;
        RUBY_NODISCARD virtual const void* GetNativeShaderHandle(ShaderStage stage) const = 0;

        RUBY_NODISCARD virtual u32 GetUniformLocation(const char* name) const = 0;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AddShader(ShaderStage stage, const String& src, bool overrideExistingStage = true) = 0;
        virtual void AddShader(const String& src, bool overrideExistingStage = true) = 0;

        RUBY_NODISCARD virtual bool IsEmpty() const = 0;
        RUBY_NODISCARD virtual bool IsReady() const = 0;

        virtual void Compile() = 0;

        virtual void SetFloat(const char* uniName, f32 value) const = 0;
        virtual void SetFloat2(const char* uniName, const glm::vec2& vec) const = 0;
        virtual void SetFloat3(const char* uniName, const glm::vec3& vec) const = 0;
        virtual void SetFloat4(const char* uniName, const glm::vec4& vec) const = 0;
        virtual void SetFloatVector(const char* uniName, const f32* data, i32 count) const = 0;

        virtual void SetInt(const char* uniName, i32 value) const = 0;
        virtual void SetInt2(const char* uniName, const glm::ivec2& vec) const = 0;
        virtual void SetInt3(const char* uniName, const glm::ivec3& vec) const = 0;
        virtual void SetInt4(const char* uniName, const glm::ivec4& vec) const = 0;
        virtual void SetIntVector(const char* uniName, const i32* data, i32 count) const = 0;

        virtual void SetMat2(const char* uniName, const glm::mat2& mat) const = 0;
        virtual void SetMat3(const char* uniName, const glm::mat3& mat) const = 0;
        virtual void SetMat4(const char* uniName, const glm::mat4& mat) const = 0;

        virtual ~Shader() = default;

    protected:
        RUBY_NODISCARD Opt<UncompiledSourcesMap> PreprocessSource(const String& src) const;
    };
}
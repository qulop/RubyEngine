#pragma once

#include <renderer/Shader.hpp>
#include <renderer/SpirV.hpp>

#include "TypesGL.hpp"


namespace Ruby::OpenGL {
    class RUBY_API ShaderGL : public Ruby::Shader {
    public:
        RUBY_NODISCARD virtual void* GetNativePipelineHandle() override;
        RUBY_NODISCARD virtual const void* GetNativePipelineHandle() const override;

        RUBY_NODISCARD virtual void* GetNativeShaderModuleHandle(ShaderStage stage);
        RUBY_NODISCARD virtual const void* GetNativeShaderModuleHandle(ShaderStage stage) const;


        RUBY_NODISCARD u32 GetUniformLocation(const char* name) const override;

        void Bind() const override;
        void Unbind() const override;

        void AddShader(ShaderStage stage, const String& path, bool overrideExistingStage) override;
        void AddShader(const String& src, bool overrideExistingStage = true) override;


        RUBY_NODISCARD bool IsEmpty() const override;
        RUBY_NODISCARD bool IsReady() const override;

        void Compile() override;

        void SetFloat(const char* uniName, f32 value) const override;
        void SetFloat2(const char* uniName, const glm::vec2& vec) const override;
        void SetFloat3(const char* uniName, const glm::vec3& vec) const override;
        void SetFloat4(const char* uniName, const glm::vec4& vec) const override;
        void SetFloatVector(const char* uniName, const f32* data, i32 count) const override;

        void SetInt(const char* uniName, i32 value) const override;
        void SetInt2(const char* uniName, const glm::ivec2& vec) const override;
        void SetInt3(const char* uniName, const glm::ivec3& vec) const override;
        void SetInt4(const char* uniName, const glm::ivec4& vec) const override;
        void SetIntVector(const char* uniName, const i32* data, i32 count) const override;

        void SetMat2(const char* uniName, const glm::mat2& mat) const override;
        void SetMat3(const char* uniName, const glm::mat3& mat) const override;
        void SetMat4(const char* uniName, const glm::mat4& mat) const override;

        ~ShaderGL() override;

    private:
        GlID CompileShader(ShaderStage type, StringView source) const;

    private:
        UniquePtr<UncompiledSourcesMap> m_sourcesToCompile;

        HashMap<ShaderStage, GlID> m_shadersId;

        GlID m_programId = RUBY_GL_UNDEFINED_ID;
        std::atomic<bool> m_isReady = false;
    };
}
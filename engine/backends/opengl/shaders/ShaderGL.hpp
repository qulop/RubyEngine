#pragma once

#include <renderer/shaders/Shader.hpp>

#include <backends/opengl/basic/TypesGL.hpp>


namespace Kiwi::OpenGL {
    class ShaderCompilerGL;


    class KIWI_API ShaderGL : public Kiwi::AShader {
    public:
        KIWI_NODISCARD virtual void* GetNativePipelineHandle() override;
        KIWI_NODISCARD virtual const void* GetNativePipelineHandle() const override;

        KIWI_NODISCARD virtual void* GetNativeShaderModuleHandle(EShaderStage stage);
        KIWI_NODISCARD virtual const void* GetNativeShaderModuleHandle(EShaderStage stage) const;

        KIWI_NODISCARD u32 GetUniformLocation(const char* name) const override;

        void Bind() const override;
        void Unbind() const override;

        KIWI_NODISCARD bool IsEmpty() const override;

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
        ShaderGL(GlID programId, HashMap<EShaderStage, GlID>&& shaderModules);

    private:
        friend class ShaderCompilerGL;

        GlID m_programId = KIWI_GL_UNDEFINED_ID;
        HashMap<EShaderStage, GlID> m_shaderModulesId;
    };
}
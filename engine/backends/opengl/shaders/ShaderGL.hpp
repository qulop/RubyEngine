#pragma once

#include <renderer/shaders/Shader.hpp>

#include <backends/opengl/basic/TypesGL.hpp>


namespace Kiwi::OpenGL {
    class ShaderCompilerGL;


    struct ShaderModuleGL final : IShaderModule {
        GlID moduleID = KIWI_GL_UNDEFINED_ID;

        KIWI_NODISCARD const void* GetNativeHandle() const override {
            return CastTo<const void*>(&moduleID);
        }

        ~ShaderModuleGL() override = default;
    };


    class KIWI_API ShaderGL final : public AShader {
        KIWI_CREATE_OBJECT(ShaderGL, AShader)

    public:
        KIWI_NODISCARD u32 GetUniformLocation(const char* name) const override;

        void Bind() const override;
        void Unbind() const override;

        KIWI_NODISCARD bool IsEmpty() const override;

        void SetFloat(const char* uniform, f32 value) const override;
        void SetFloat2(const char* uniform, const glm::vec2& vec) const override;
        void SetFloat3(const char* uniform, const glm::vec3& vec) const override;
        void SetFloat4(const char* uniform, const glm::vec4& vec) const override;
        void SetFloatVector(const char* uniform, const f32* data, i32 count) const override;

        void SetInt(const char* uniform, i32 value) const override;
        void SetInt2(const char* uniform, const glm::ivec2& vec) const override;
        void SetInt3(const char* uniform, const glm::ivec3& vec) const override;
        void SetInt4(const char* uniform, const glm::ivec4& vec) const override;
        void SetIntVector(const char* uniform, const i32* data, i32 count) const override;

        void SetMat2(const char* uniform, const glm::mat2& mat) const override;
        void SetMat3(const char* uniform, const glm::mat3& mat) const override;
        void SetMat4(const char* uniform, const glm::mat4& mat) const override;

        ~ShaderGL() override;

    private:
        ShaderGL(GlID programId, Map<EShaderStage, ShaderModuleGL>&& shaderModules);

    private:
        friend class ShaderCompilerGL;

        GlID m_programId = KIWI_GL_UNDEFINED_ID;
    };
}

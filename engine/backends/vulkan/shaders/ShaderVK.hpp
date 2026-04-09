#pragma once

#include <renderer/shaders/Shader.hpp>

#include <vulkan/vulkan.h>



namespace Kiwi::Vulkan {
    class ShaderVK : public AShader {
    public:
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

        ~ShaderVK() override;

    private:
        ShaderVK(HashMap<EShaderStage, VkShaderModule>&& shaderModules);
    };
}
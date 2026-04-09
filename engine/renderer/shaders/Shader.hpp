#pragma once

#include <common/PCH.hpp>
#include <common/hash/Hash.hpp>
#include <common/Definitions.hpp>

#include <core/Object.hpp>

#include <renderer/shaders/ShaderStage.hpp>

#include <glm/glm.hpp>
#include <glad/glad.h>


namespace Kiwi {
    struct ShaderCacheEntry;
    class AShaderCompiler;


    KIWI_INTERFACE IShaderModule {
        KIWI_NODISCARD virtual const void* GetNativeHandle() const = 0;

        virtual ~IShaderModule() = default;
    };


    class KIWI_API AShader : public AObject {
        KIWI_CREATE_OBJECT(AShader, AObject)

    public:
        KIWI_NODISCARD static Opt<EShaderStage> StringToShaderStage(StringView stageName);

    public:
        KIWI_NODISCARD virtual u32 GetUniformLocation(const char* name) const = 0;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        KIWI_NODISCARD virtual bool IsEmpty() const = 0;

        virtual void SetFloat(const char* uniform, f32 value) const = 0;
        virtual void SetFloat2(const char* uniform, const glm::vec2& vec) const = 0;
        virtual void SetFloat3(const char* uniform, const glm::vec3& vec) const = 0;
        virtual void SetFloat4(const char* uniform, const glm::vec4& vec) const = 0;
        virtual void SetFloatVector(const char* uniform, const f32* data, i32 count) const = 0;

        virtual void SetInt(const char* uniform, i32 value) const = 0;
        virtual void SetInt2(const char* uniform, const glm::ivec2& vec) const = 0;
        virtual void SetInt3(const char* uniform, const glm::ivec3& vec) const = 0;
        virtual void SetInt4(const char* uniform, const glm::ivec4& vec) const = 0;
        virtual void SetIntVector(const char* uniform, const i32* data, i32 count) const = 0;

        virtual void SetMat2(const char* uniform, const glm::mat2& mat) const = 0;
        virtual void SetMat3(const char* uniform, const glm::mat3& mat) const = 0;
        virtual void SetMat4(const char* uniform, const glm::mat4& mat) const = 0;

        ~AShader() override = default;

    protected:
        template<Concepts::DerivedFrom<IShaderModule> THandle>
        explicit AShader(Map<EShaderStage, THandle>&& shaderModules) {
            for (auto& [stage, module] : shaderModules) {
                m_shaderModules[stage] = MakeUnique<THandle>(std::move(module));
            }
        }

        friend class AShaderCompiler;

        Map<EShaderStage, UniquePtr<IShaderModule>> m_shaderModules;
    };
}
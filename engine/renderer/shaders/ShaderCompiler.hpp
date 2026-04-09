#pragma once

#include <core/Object.hpp>

#include <common/meta/TypeTraits.hpp>
#include <common/filesystem/File.hpp>

#include <common/Definitions.hpp>

#include <renderer/shaders/ShaderStage.hpp>
#include <renderer/shaders/PreprocessorGLSL.hpp>
#include <renderer/shaders/Shader.hpp>
#include <renderer/shaders/SpirV.hpp>



namespace Kiwi {
    class AShaderCompiler : public AObject {
        KIWI_CREATE_OBJECT(AShaderCompiler, AObject)

    public:
        struct CompilationDetails {
            ESpirVEnvironment environment = ESpirVEnvironment::Vulkan;
            ESpirVOptimizationLevel optimizationLvl = ESpirVOptimizationLevel::PERFORMANCE;
            PreprocessorGLSL::SourcesMap preprocessedSrc;
        };

    public:
        template<Concepts::DerivedFrom<SelfType> T, typename... Args>
        KIWI_NODISCARD static UniquePtr<SelfType> Create(Args&&... args) {
            return MakeUnique<T>(std::forward<Args>(args)...);
        }

        KIWI_NODISCARD static Opt<PreprocessorGLSL::SourcesMap> PreprocessSource(const String& src);
        KIWI_NODISCARD static Result<Map<EShaderStage, Vector<u32>>> CompileToSpirV(const CompilationDetails& compilationDetails);

        KIWI_NODISCARD static Result<Map<EShaderStage, Vector<u32>>> PreprocessAndCompileToSpirV(const File& sourceFile, ESpirVEnvironment env, ESpirVOptimizationLevel optimizationLvl);

    public:
        KIWI_NODISCARD virtual UniquePtr<AShader> CompileFile(const File& sourceFile) = 0;

        ~AShaderCompiler() override = default;
    };
}
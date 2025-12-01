#pragma once

#include <types/TypeTraits.hpp>
#include <types/File.hpp>

#include <utility/Definitions.hpp>
#include <utility/Assert.hpp>

#include <renderer/shaders/ShaderStage.hpp>
#include <renderer/shaders/PreprocessorGLSL.hpp>
#include <renderer/shaders/Shader.hpp>



namespace Kiwi {
    KIWI_ABSTRACT class AShaderCompiler {
        using ThisClass = AShaderCompiler;

    public:
        template<Concepts::DerivedFrom<ThisClass> T, typename... Args>
        KIWI_NODISCARD static UniquePtr<ThisClass> Create(Args&&... args) {
            return MakeUnique<T>(std::forward<Args>(args)...);
        }

    public:
        KIWI_NODISCARD virtual UniquePtr<AShader> CompileFile(const File& sourceFile) = 0;

        virtual ~AShaderCompiler() = default;

    public:
        KIWI_NODISCARD static Opt<typename PreprocessorGLSL::SourcesMap> PreprocessSource(const String& src) {
            PreprocessorGLSL preprocessor;

            auto res = preprocessor.Preprocess(src);
            if (res) {
                return *res;
            }

            auto kind = res.error().kind;
            KIWI_ASSERT_BASIC(kind != GlslPreprocessError::NONE);

            // TODO: Idk where am i should output error messages, so for now just skip it
            switch (kind) {
                case GlslPreprocessError::INCORRECT_STAGE_NAME:
                    break;
                case GlslPreprocessError::END_OF_STAGE_MISSED:
                    break;
                case GlslPreprocessError::TOKEN_ALREADY_DECLARED:
                    break;
                case GlslPreprocessError::INCORRECT_PREPROCESSOR_PROPERTIES_COUNT:
                    break;
            }

            return nullopt;
        }
    };
}
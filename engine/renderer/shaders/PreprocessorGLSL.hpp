#pragma once

#include "Shader.hpp"

#include <misc/ParserBase.hpp>


namespace Ruby {
    // Struct(instead of enum class) reserved for the future purposes
    struct GlslPreprocessError {
        enum EErrorKind {
            NONE,
            INCORRECT_STAGE_NAME,
            END_OF_STAGE_MISSED,
            TOKEN_ALREADY_DECLARED,
            INCORRECT_PREPROCESSOR_PROPERTIES_COUNT
        };

        EErrorKind kind = EErrorKind::NONE;
    };


    class PreprocessorGLSL : protected Misc::ParserBase {
        using PreprocessResult = std::expected<typename AShader::UncompiledSourcesMap, GlslPreprocessError>;
        using PreprocessorProperties= std::pair<String, Vector<String>>;

    public:
        PreprocessorGLSL() = default;

    public:
        RUBY_NODISCARD PreprocessResult Preprocess(const String& src);

    private:
        RUBY_NODISCARD Opt<size_t> FindPreprocessorPosition(StringView token) const;

        RUBY_NODISCARD Opt<PreprocessorProperties> ExtractPreprocessor(StringView token);
    };
}
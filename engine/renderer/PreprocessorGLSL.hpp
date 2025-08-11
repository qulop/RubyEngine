#pragma once

#include "Shader.hpp"

#include <misc/ParserBase.hpp>


namespace Ruby {
    // Struct(instead of enum class) reserved for future
    struct GlslPreprocessError {
        enum ErrorKind {
            NONE,
            INCORRECT_STAGE_NAME,
            END_OF_STAGE_MISSED,
            TOKEN_ALREADY_DECLARED,
            INCORRECT_PREPROCESSOR_PROPERTIES_COUNT
        };

        ErrorKind kind = ErrorKind::NONE;
    };


    class PreprocessorGLSL : protected Misc::ParserBase {
        using PreprocessResult = std::expected<typename Shader::UncompiledSourcesMap, GlslPreprocessError>;
        using PreprocessorProperties= std::pair<String, Vector<String>>;

    public:
        PreprocessorGLSL() = default;

    public:
        RUBY_NODISCARD PreprocessResult TryPreprocess(const String& src);

    private:
        RUBY_NODISCARD Opt<PreprocessorProperties> TryToFindPreprocessor(StringView token);
    };
}
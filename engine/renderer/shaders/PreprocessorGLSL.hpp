#pragma once

#include "Shader.hpp"

#include <misc/ParserBase.hpp>


namespace Kiwi {
    // Struct(instead of enum class) reserved for the future purposes
    struct GlslPreprocessError {
        enum EErrorKind {
            NONE,
            INCORRECT_STAGE_NAME,
            END_OF_STAGE_MISSED,
            TOKEN_ALREADY_DECLARED,
            INCORRECT_PREPROCESSOR_PROPERTIES_COUNT,
            SHADER_VERSION_MISSING,
        };

        EErrorKind kind = EErrorKind::NONE;
    };


    class PreprocessorGLSL : protected Misc::ParserBase {
    public:
        using SourcesMap = HashMap<EShaderStage, String>;
        using PreprocessResult = std::expected<SourcesMap, GlslPreprocessError>;
        using PreprocessorProperties= std::pair<String, Vector<String>>;

    public:
        PreprocessorGLSL() = default;

    public:
        KIWI_NODISCARD PreprocessResult Preprocess(const String& src);

    private:
        KIWI_NODISCARD Opt<size_t> FindPreprocessorPosition(StringView token);

        KIWI_NODISCARD Opt<PreprocessorProperties> ExtractPreprocessor(StringView token);
    };
}
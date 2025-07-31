#pragma once

#include "Shader.hpp"

#include <expected>


namespace Ruby {
    enum class GlslPreprocessError {
        INCORRECT_STAGE_NAME,
        END_OF_STAGE_MISSED
    };


    class PreprocessorGLSL final {
        using PreprocessResult = std::expected<typename Shader::UncompiledSourcesMap, GlslPreprocessError>;

    public:
        PreprocessorGLSL() = delete;

    public:
        static RUBY_NODISCARD PreprocessResult TryPreprocess(const String& src);

    private:
        static RUBY_NODISCARD std::string_view GetFirstPreprocessDirective(std::string_view src, size_t& cursor);

        static RUBY_NODISCARD bool IsStageBegin(std::string_view src, size_t tokenBegin);

        static RUBY_NODISCARD Opt<ShaderStage> ExtractShaderStageName(std::string_view stageSrc);
        static RUBY_NODISCARD Opt<ShaderStage> StringToShaderStage(std::string_view stageName);
    };
}
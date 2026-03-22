#include "PreprocessorGLSL.hpp"

#include <common/Algorithm.hpp>
#include <common/cast/Cast.hpp>
#include <common/types/String.hpp>


namespace {
    constexpr Kiwi::StringView VERSION_TOKEN_NAME = "version";
    constexpr Kiwi::StringView STAGE_BEGIN_TOKEN_NAME = "stage";
    constexpr Kiwi::StringView STAGE_END_TOKEN_NAME = "endstage";
}


namespace Kiwi {
    PreprocessorGLSL::PreprocessResult PreprocessorGLSL::Preprocess(const String& src) {
        Reset(src);

        SourcesMap result;

        auto&& [_, versionProps] = ExtractPreprocessor(VERSION_TOKEN_NAME).value_or(PreprocessorProperties{});
        if (versionProps.empty()) {
            return std::unexpected(GlslPreprocessError{
                .kind = GlslPreprocessError::SHADER_VERSION_MISSING
            });
        }

        while (true) {
            auto&& [preprocName, preprocProps] = ExtractPreprocessor(STAGE_BEGIN_TOKEN_NAME)
                .value_or(std::make_pair(String{}, Vector<String>{}));

            if (preprocName.empty() || preprocName != STAGE_BEGIN_TOKEN_NAME) {
                if (preprocName.empty()) {
                    break;
                }
                continue;
            }

            if (preprocProps.size() != 1) {
                return std::unexpected(GlslPreprocessError{
                    .kind = GlslPreprocessError::INCORRECT_PREPROCESSOR_PROPERTIES_COUNT
                });
            }

            auto shaderStageName = AShader::StringToShaderStage(preprocProps.at(0));
            if (!shaderStageName) {
                return std::unexpected(GlslPreprocessError{
                    .kind = GlslPreprocessError::INCORRECT_STAGE_NAME
                });
            }

            auto stageCodeBeginPos = JumpToNextLine();
            auto stageCodeEndPos = FindPreprocessorPosition(STAGE_END_TOKEN_NAME).value_or(StringView::npos);

            if (stageCodeEndPos == StringView::npos) {
                return std::unexpected(GlslPreprocessError{
                    .kind = GlslPreprocessError::END_OF_STAGE_MISSED
                });
            }

            String& shaderStageCode = result[*shaderStageName];
            if (!versionProps.empty()) {
                shaderStageCode = std::format("#version {}\n", StringUtils::Join(std::span<String>{ versionProps }));
            }

            result[*shaderStageName] += src.substr(stageCodeBeginPos, stageCodeEndPos - stageCodeBeginPos);
            m_currPos = stageCodeEndPos + 1;
        }

        return result;
    }

    Opt<size_t> PreprocessorGLSL::FindPreprocessorPosition(StringView token) {
        size_t searchPos = m_currPos;
        while ((searchPos = m_src.find_first_of('#', m_currPos)) != StringView::npos) {
            size_t tokenBegin = m_src.find_first_not_of(Globals::Misc::WHITESPACE, searchPos + 1);

            auto optCurrToken = GetCurrentToken(tokenBegin);
            if (!optCurrToken) {
                return nullopt;
            }

            if (*optCurrToken == token) {
                return searchPos;
            }

            searchPos = m_currPos = (tokenBegin + token.length());
        }

        return nullopt;
    }

    Opt<PreprocessorGLSL::PreprocessorProperties> PreprocessorGLSL::ExtractPreprocessor(StringView token) {
        auto pos = FindPreprocessorPosition(token).value_or(StringView::npos);
        if (pos == StringView::npos) {
            return nullopt;
        }

        pos = m_src.find_first_not_of(Globals::Misc::WHITESPACE, pos + 1);
        String foundPreprocessor = GetCurrentToken(pos).value_or("");
        if (foundPreprocessor.empty()) {
            return nullopt;
        }

        pos += foundPreprocessor.size() + 1;
        auto c = m_src.substr(pos);

        size_t endOfLinePos = m_src.find_first_of(Globals::Misc::END_OF_LINE, pos);
        if (endOfLinePos == StringView::npos) {
            return nullopt;
        }

        auto properties = Tokenize(pos, endOfLinePos);

        m_currPos = pos + 1;
        return std::make_pair(
            std::move(foundPreprocessor),
            std::move(*properties)
        );
    }
}
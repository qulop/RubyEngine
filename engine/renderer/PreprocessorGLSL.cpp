#include "PreprocessorGLSL.hpp"

#include <utility/Algorithm.hpp>
#include <utility/Cast.hpp>


namespace {
    constexpr Ruby::StringView VERSION_TOKEN_NAME = "#version";
    constexpr Ruby::StringView STAGE_BEGIN_TOKEN_NAME = "#stage";
    constexpr Ruby::StringView STAGE_END_TOKEN_NAME = "#endstage";
}


namespace Ruby {
    PreprocessorGLSL::PreprocessResult PreprocessorGLSL::TryPreprocess(const String& src) {
        Reset(src);

        Shader::UncompiledSourcesMap result;

        auto versionForwardDecl = TryToFindPreprocessor(VERSION_TOKEN_NAME);

        while (true) {
            auto optNextPreprocessor = TryToFindPreprocessor(STAGE_BEGIN_TOKEN_NAME);
            if (!optNextPreprocessor) {
                break;
            }

            const auto& [preprocName, preprocValues] = *optNextPreprocessor;
            if (preprocName != STAGE_BEGIN_TOKEN_NAME) {
                continue;
            }

            if (preprocValues.empty() || preprocValues.size() >  1) {
                return std::unexpected(GlslPreprocessError{
                    .kind = GlslPreprocessError::INCORRECT_PREPROCESSOR_PROPERTIES_COUNT
                });
            }

            auto shaderStageName = Shader::StringToShaderStage(preprocValues.at(0));
            if (!shaderStageName) {
                return std::unexpected(GlslPreprocessError{
                    .kind = GlslPreprocessError::INCORRECT_STAGE_NAME
                });
            }

            auto stageCodeBeginPos = JumpToNextLine();
            auto stageCodeEndPos = findSubString(src, STAGE_END_TOKEN_NAME, stageCodeBeginPos);

            if (stageCodeEndPos == RUBY_BAD_INDEX) {
                return std::unexpected(GlslPreprocessError{
                    .kind = GlslPreprocessError::END_OF_STAGE_MISSED
                });
            }

            String& shaderStageCode = result[*shaderStageName];
            if (versionForwardDecl) {
                shaderStageCode = std::format("{}\n", *versionForwardDecl);
            }

            result[*shaderStageName] += src.substr(stageCodeBeginPos, stageCodeEndPos - stageCodeBeginPos);
            m_currPos = stageCodeEndPos + 1;
        }

        return result;
    }

    Opt<PreprocessorGLSL::PreprocessorProperties> PreprocessorGLSL::TryToFindPreprocessor(StringView token) {
        size_t searchPos = m_currPos;
        while ((searchPos = m_src.find_first_of('#', m_currPos)) != StringView::npos) {
            auto optCurrToken = GetCurrentToken(searchPos);
            if (!optCurrToken)  return nullopt;

            const auto& foundToken = *optCurrToken;
            if (foundToken != token) {
                ++searchPos;
                continue;
            }
            searchPos += foundToken.size() + 1;

            size_t endOfLinePos = m_src.find_first_of(Globals::Misc::END_OF_LINE, searchPos);
            if (endOfLinePos == StringView::npos)   return nullopt;

            auto properties = Tokenize(searchPos, endOfLinePos);

            m_currPos = searchPos + 1;
            return std::make_pair(
                String{ *optCurrToken },
                std::move(*properties)
            );
        }

        return nullopt;
    }
}
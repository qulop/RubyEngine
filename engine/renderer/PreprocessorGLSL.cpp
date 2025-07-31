#include "PreprocessorGLSL.hpp"

#include <utility/Algorithm.hpp>


#define RUBY_UPDATE_CURSOR_POSITION(newPos)     newPos


namespace {
    constexpr std::string_view VERSION_KEYWORD = "#version";
    constexpr std::string_view STAGE_BEGIN_KEYWORD = "#stage";
    constexpr std::string_view STAGE_END_KEYWORD = "#endstage";
    constexpr std::string_view END_OF_TOKEN = { " \n\r\0\t", 5 };
}


namespace Ruby {
    PreprocessorGLSL::PreprocessResult PreprocessorGLSL::TryPreprocess(const String& src) {
        size_t cursor = 0;
        bool requiresVersionInjection = GetFirstPreprocessDirective(src, cursor) == VERSION_KEYWORD;

        Shader::UncompiledSourcesMap result;

        size_t stageBegin = 0;
        while ((stageBegin = src.find_first_of('#', cursor)) != String::npos) {
            if (!IsStageBegin(src, stageBegin)) {
                cursor = RUBY_UPDATE_CURSOR_POSITION(stageBegin + 1);
                continue;
            }

            auto optStageName = ExtractShaderStageName(
                std::string_view{ src }.substr(stageBegin)
            );
            if (!optStageName) {
                return std::unexpected(GlslPreprocessError::INCORRECT_STAGE_NAME);
            }

            stageBegin = src.find_first_of('\n', stageBegin) + 1;
            auto stageEnd = findSubString(src, STAGE_END_KEYWORD, stageBegin);
            if (stageEnd == RUBY_BAD_INDEX) {
                return std::unexpected(GlslPreprocessError::END_OF_STAGE_MISSED);
            }

            result[optStageName.value()] = src.substr(stageBegin, stageEnd - stageBegin);
            cursor = RUBY_UPDATE_CURSOR_POSITION(stageEnd + 1);
        }

        return result;
    }

    std::string_view PreprocessorGLSL::GetFirstPreprocessDirective(std::string_view src, size_t& cursor) {
        size_t tokenBegin = src.find_first_of('#');
        size_t tokenEnd = src.find_first_of(END_OF_TOKEN, tokenBegin);

        return src.substr(tokenBegin, tokenEnd);
    }


    bool PreprocessorGLSL::IsStageBegin(std::string_view src, size_t tokenBegin) {
        auto token = src.substr(tokenBegin, STAGE_BEGIN_KEYWORD.size());

        return token == STAGE_BEGIN_KEYWORD;
    }

    Opt<ShaderStage> PreprocessorGLSL::ExtractShaderStageName(std::string_view stageSrc) {
        stageSrc.remove_prefix(STAGE_BEGIN_KEYWORD.size());

        size_t stageNameBeginPos = stageSrc.find_first_not_of(' ');
        if (stageNameBeginPos == std::string_view::npos) {
            return Ruby::nullopt;
        }
        stageSrc.remove_prefix(stageNameBeginPos);

        size_t stageNameEndPos = stageSrc.find_first_of(END_OF_TOKEN);
        if (stageNameEndPos == std::string_view::npos) {
            return Ruby::nullopt;
        }

        auto stageName = stageSrc.substr(0, stageNameEndPos);
        return StringToShaderStage(stageName);
    }

    Opt<ShaderStage> PreprocessorGLSL::StringToShaderStage(std::string_view stageName) {
        using namespace Ruby;

        if (stageName == "vertex")     return ShaderStage::VERTEX;
        else if (stageName == "geometry")   return ShaderStage::GEOMETRY;
        else if (stageName == "fragment")   return ShaderStage::FRAGMENT;
        else if (stageName == "compute")    return ShaderStage::COMPUTE;

        return nullopt;
    }
}
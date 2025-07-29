#include "Shader.hpp"

#include <utility/Algorithm.hpp>
#include <types/Logger.hpp>



namespace {
    constexpr std::string_view STAGE_BEGIN_KEYWORD = "#stage";
    constexpr std::string_view STAGE_END_KEYWORD = "#endstage";
    constexpr std::string_view END_OF_TOKEN = "\n\0\t ";


    bool isStageBegin(std::string_view src, size_t tokenBegin) {
        size_t tokenEnd = src.find_first_of(' ');

        if (tokenEnd == std::string_view::npos) {
            return false;
        }
        else if ((tokenEnd - tokenBegin) != STAGE_BEGIN_KEYWORD.size()) {
            return false;
        }
        
        auto token = src.substr(tokenBegin, tokenEnd);
        return token == STAGE_BEGIN_KEYWORD;
    }

    Ruby::Opt<Ruby::ShaderStage> stringToShaderStage(std::string_view stageName) {
        using namespace Ruby;

        if      (stageName == "vertex")     return ShaderStage::VERTEX;
        else if (stageName == "geometry")   return ShaderStage::GEOMETRY;
        else if (stageName == "fragment")   return ShaderStage::FRAGMENT;
        else if (stageName == "compute")    return ShaderStage::COMPUTE;

        RUBY_ERROR("stringToShaderStage() : Unknown stage name - {}",
                   stageName
        );
        return nullopt;
    }

    Ruby::Opt<Ruby::ShaderStage> extractShaderStageName(std::string_view stageSrc) {
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
        return stringToShaderStage(stageName);
    }
}


namespace Ruby {
    Opt<Shader::UncompiledSourcesMap> Shader::SplitUnifiedShaderSource(const String& src) const {
        UncompiledSourcesMap result;
        
        size_t cursor = 0;
        size_t stageBegin = 0;
        while ((stageBegin = src.find_first_of('#', cursor)) != String::npos) {
            if (!isStageBegin(src, stageBegin)) {
                cursor = stageBegin + 1;
                continue;
            }

            auto optStageName = extractShaderStageName(
                std::string_view{ src }.substr(stageBegin)
            );
            if (!optStageName) {
                return nullopt;
            }

            stageBegin = src.find_first_of(END_OF_TOKEN, stageBegin) + 1;
            auto stageEnd = findSubString(src, STAGE_END_KEYWORD, stageBegin);
            if (stageEnd == RUBY_BAD_INDEX) {
                RUBY_ERROR("Shader::SplitUnifiedShaderSource() : Failed to find closing directive for '#stage'");
                return nullopt;
            }

            result[optStageName.value()] = src.substr(stageBegin, stageEnd - stageBegin);
        }

        return result;
    }
}
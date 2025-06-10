#include "EngineGlobalConfig.hpp"

#include <utility/Cast.hpp>


namespace {
    Ruby::String getParentPath(const Ruby::String& path) {
        std::filesystem::path fsPath{ path };

        return fsPath.parent_path().string();
    }
}

namespace Ruby {


    void EngineGlobalConfig::InitFromCommandLine(ProgramOptions&& opts) {
        if (opts.HasOption("max-fps"))
            maxFPS = std::any_cast<i32>(opts.GetArgumentOfOption("max-fps"));

        applicationDirectory = std::move(getParentPath(opts.GetAppPath()));

        if (opts.HasOption("log-directory"))
            loggerBaseDirectory = std::any_cast<String>(opts.GetArgumentOfOption("log-directory"));
        else
            loggerBaseDirectory = applicationDirectory;


        videoConfig.width = std::any_cast<i32>(opts.GetArgumentOfOption("width"));
        videoConfig.height = std::any_cast<i32>(opts.GetArgumentOfOption("height"));
        videoConfig.isResizable = std::any_cast<bool>(opts.GetArgumentOfOption("resizable"));
        videoConfig.isFullScreened = opts.HasOption("full-screen");

        engineLocale = Platform::Locale::GetSystemLocale().value_or(L"");
        engineEncoding = Platform::Locale::GetSystemEncoding().value_or(L"");
    }


    namespace Globals {
        EngineGlobalConfig globalConfig;
    }
}

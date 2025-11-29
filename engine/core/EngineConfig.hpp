#pragma once

#include <utility/ProgramOptions.hpp>
#include <utility/Definitions.hpp>

#include <types/Logger.hpp>


namespace Ruby {
    const String OPT_VSYNC_ENABLE = "VSyncEnable";
    const String OPT_FULL_SCREEN = "FullScreen";
    const String OPT_MAX_FPS = "MaxFPS";
    const String OPT_ENGINE_OUT_DIR = "EngineOutDir";
    const String OPT_APPLICATION_OUT_DIR = "ApplicationOutDir";
    const String OPT_WINDOW_NAME = "MainWindowName";
    const String OPT_LOG_NAME = "LogFileName";


    struct EngineConfig {
    public:
        RUBY_NODISCARD static Vector<CmdLineOption> GetCommandLineOptions();
    };
}
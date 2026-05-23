#pragma once

#include <common/ProgramOptions.hpp>
#include <common/Definitions.hpp>

#include <common/Version.hpp>


namespace Kiwi {
    const String OPT_VSYNC_ENABLE = "VSyncEnable";
    const String OPT_FULL_SCREEN = "FullScreen";
    const String OPT_MAX_FPS = "MaxFPS";
    const String OPT_ENGINE_OUT_DIR = "EngineOutDir";
    const String OPT_APPLICATION_OUT_DIR = "ApplicationOutDir";
    const String OPT_WINDOW_NAME = "MainWindowName";
    const String OPT_LOG_NAME = "LogFileName";


    struct EngineConfig {
    public:
        static constexpr Version ENGINE_VERSION = Version(1, 0, 0);
        static constexpr StringView ENGINE_NAME = "Kiwi Engine";

    #ifdef KIWI_DEBUG_BUILD
        static constexpr bool ENABLE_DEBUG_CAPABILITIES = true;
    #else
        static constexpr bool ENABLE_DEBUG_CAPABILITIES = false;
    #endif

    public:
        KIWI_NODISCARD static Vector<CmdLineOption> GetCommandLineOptions();
    };
}
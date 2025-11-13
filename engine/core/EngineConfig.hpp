#pragma once

#include <misc/WindowProps.hpp>

#include <utility/ProgramOptions.hpp>
#include <utility/Definitions.hpp>

#include <types/Logger.hpp>


namespace Ruby {
    constexpr String OPT_VSYNC_ENABLE = "VSyncEnable";
    constexpr String OPT_FULL_SCREEN = "FullScreen";
    constexpr String OPT_MAX_FPS = "MaxFPS";
    constexpr String OPT_ENGINE_OUT_DIR = "EngineOutDir";


    struct EngineConfig {
    public:
        RUBY_NODISCARD static Vector<CmdLineOption> GetCommandLineOptions();
    };
}
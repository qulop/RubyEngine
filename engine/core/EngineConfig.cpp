#include "EngineConfig.hpp"

#include <types/cast/Cast.hpp>
#include <utility/ProgramOptions.hpp>



namespace Kiwi {
    u8 EngineConfig::ENGINE_MAJOR_VERSION = 1;
    u8 EngineConfig::ENGINE_MINOR_VERSION = 0;
    u8 EngineConfig::ENGINE_PATCH_VERSION = 0;


    Vector<CmdLineOption> EngineConfig::GetCommandLineOptions() {
        return Vector<CmdLineOption> {
            CmdLineOption(OPT_VSYNC_ENABLE, EOptionArgType::BOOL),
            CmdLineOption(OPT_FULL_SCREEN, EOptionArgType::BOOL),
            CmdLineOption(OPT_MAX_FPS, EOptionArgType::INT),
            CmdLineOption(OPT_ENGINE_OUT_DIR, EOptionArgType::PATH),
            CmdLineOption(OPT_APPLICATION_OUT_DIR, EOptionArgType::PATH),
            CmdLineOption(OPT_WINDOW_NAME, EOptionArgType::STRING),
            CmdLineOption(OPT_LOG_NAME, EOptionArgType::STRING)
        };
    }

    EngineInfo EngineConfig::GetDefaultInfo() {
        return EngineInfo {
            .engineName = "Kiwi Engine",
            .engineVersion = Version(ENGINE_MAJOR_VERSION, ENGINE_MINOR_VERSION, ENGINE_PATCH_VERSION),
        };
    }
}

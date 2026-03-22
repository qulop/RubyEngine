#include "EngineConfig.hpp"

#include <common/cast/Cast.hpp>
#include <utility/ProgramOptions.hpp>



namespace Kiwi {
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

}

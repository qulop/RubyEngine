#ifdef RUBY_RELEASE_BUILD
    #define _NDEBUG
#endif

#include "utility/ProgramOptions.hpp"
#include "platform/Platform.hpp"
#include "misc/Application.hpp"


namespace {
    Ruby::ProgramOptions getApplicationOptions(int argc, char** argv) {
        using namespace Ruby;

        auto&& [defaultWidth, defaultHeight] = Platform::getScreenResolution();

        std::initializer_list<CmdLineOption> optionsList = {
            { "width", OptionArgType::INT, defaultWidth },
            { "height", OptionArgType::INT, defaultHeight },
            { "resizable", OptionArgType::BOOL, true },
            { "log-directory", OptionArgType::STRING },
            { "full-screen", OptionArgType::NONE },
            { "max-fps", OptionArgType::INT }
        };

        return ProgramOptions{ argc, argv, optionsList };
    }
}


Ruby::i32 main(int argc, char** argv) {
    using namespace Ruby;

    auto options = getApplicationOptions(argc, argv);
    if (!options.IsParseProcessed()) {
        return EXIT_FAILURE;
    }

    auto& app = Application::GetInstance();
    app.InitApplication(std::move(options));

    if (!app.IsInitialized()) {
        Platform::writeInConsole("Failed to initialize an application (╥﹏╥)");
        return EXIT_FAILURE;
    }

    app.StartApplication();
    return EXIT_SUCCESS;
}
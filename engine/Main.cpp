#ifdef RUBY_RELEASE_BUILD
    #define _NDEBUG
#endif

#include "platform/io/SystemConsole.hpp"
#include "platform/Platform.hpp"

#include "core/Application.hpp"
#include "utility/Time.hpp"


Ruby::i32 main(int argc, char** argv) {
    using namespace Ruby;

    i32 exitCode = RUBY_EXIT_SUCCESS;
    {
        auto app = MakeUnique<Application>();
        if (!app->Init()) {
            return RUBY_EXIT_FAILURE;
        }

        exitCode = app->Run();
    }

    return exitCode;
}
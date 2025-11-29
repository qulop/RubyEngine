#ifdef RUBY_RELEASE_BUILD
    #define _NDEBUG
#endif

#include <core/EntryPoint.hpp>
#include <core/Application.hpp>


namespace Ruby {
    i32 RubyEntryPoint(i32 argc, char** argv) {
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
}

#ifdef RUBY_WIN32_USED
    int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR pCmdLine, int nCmdShow) {
        return Ruby::RubyEntryPoint(0, nullptr);        
    }
#endif
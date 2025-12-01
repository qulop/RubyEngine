#ifdef KIWI_RELEASE_BUILD
    #define _NDEBUG
#endif

#include <core/EntryPoint.hpp>
#include <core/Application.hpp>

#include <sync/Thread.hpp>


namespace Kiwi {
    i32 EntryPoint(i32 argc, char** argv) {
        using namespace Kiwi;

        Sync::Thread::RegisterThisThreadAsMain();


        i32 exitCode = KIWI_EXIT_SUCCESS;
        {
            auto app = MakeUnique<Application>();
            if (!app->Init()) {
                return KIWI_EXIT_FAILURE;
            }

            exitCode = app->Run();
        }

        return exitCode;
    }
}

#ifdef KIWI_WIN32_USED
    int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR pCmdLine, int nCmdShow) {
        return Kiwi::EntryPoint(0, nullptr);
    }
#endif
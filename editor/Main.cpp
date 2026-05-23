#ifdef KIWI_RELEASE_BUILD
    #define _NDEBUG
#endif

#include <core/EntryPoint.hpp>
#include <core/Application.hpp>

#include <common/PCH.hpp>

#include <platform/Platform.hpp>

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
    #ifdef KIWI_MSVC_USED
        return Kiwi::EntryPoint(__argc, __argv);
    #else
        Kiwi::Vector<Kiwi::String> args = Kiwi::Platform::GetApplicationArguments();
        Kiwi::Vector<char*> argv = args
            | std::views::transform([](Kiwi::String& s) -> char* { return s.GetMutableRaw(); })
            | std::ranges::to<Kiwi::Vector<char*>>();

        return Kiwi::EntryPoint(static_cast<Kiwi::i32>(argv.size()), argv.data());
    #endif
    }
#endif
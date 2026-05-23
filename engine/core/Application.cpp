#include "Application.hpp"

#include <renderer/shaders/ShaderCacheManager.hpp>

#include <sync/Atomic.hpp>

#include <common/Time.hpp>

#include <profiler/EngineProfiler.hpp>

#include <core/Object.hpp>
#include <core/EngineConfig.hpp>
#include <core/LogSubsystem.hpp>

#include <platform/io/SystemConsole.hpp>

#include <misc/WindowSubsystem.hpp>



namespace Kiwi {
    Path Application::s_applicationOutputDirectory = Path{};


    Path Application::GetApplicationOutputDirectory() {
        KIWI_ASSERT_BASIC(!s_applicationOutputDirectory.empty());

        return s_applicationOutputDirectory;
    }

    bool Application::Init() {
    #ifdef KIWI_DEBUG_BUILD
        if (!Platform::CreateDebugConsole()) {
            return false;
        }
    #endif

        s_subsystems = KIWI_NOTHROW_NEW SubsystemHolderType();
        if (!s_subsystems) {
            Console::WriteLine("Failed to allocate memory for the subsystems holder");
            return false;
        }

    #if 0
        if (EngineProfiler::IsEnabled() && !EngineProfiler::IsConnectedToServer()) {
            Console::WriteLine("Connection to the profiler server failed to establish");
            return false;
        }
    #endif

        m_cliOptions = ProgramOptions::Parse(Platform::GetApplicationArguments()).value_or(ProgramOptions());
        if (m_cliOptions.IsEmpty()) {
            Console::WriteLine("Failed to parse command line arguments");
            return false;
        }

        s_applicationOutputDirectory = m_cliOptions
            .Get<Path>(OPT_APPLICATION_OUT_DIR)
            .value_or(Platform::GetTemporaryDirectoryPath());


        LoggerInitInfo loggerInfo {
            .loggerPathDirectory = GetApplicationOutputDirectory()
        };
        RegisterSubsystem<LogSubsystem>(loggerInfo);
        if (!GetSubsystem<LogSubsystem>()->Init()) {
            return false;
        }

        KIWI_IGNORE_RETURN(ShaderCacheManager::Init());

        RegisterSubsystem<WindowSubsystem>();
        GetSubsystem<WindowSubsystem>()->Init();

        m_engine = MakeShared<Engine>();
        if (!m_engine->Init(m_cliOptions)) {
            KIWI_CTX_LOG(ERROR, "Failed to initialize the engine instance");
            return false;
        }

        m_isInitialized.store(true);
        return true;
    }

    void Application::BeforeShutdown() {
        delete s_subsystems;
    }

    i32 Application::Run() {
        KIWI_ASSERT(m_isInitialized.load(), "You must initialize an application first");

        BeforeRun();

        while (true) {
            BeforeFrameBegin();

            this->Update();

            if (!m_engine->Update()) {
                break;
            }

            BeforeFrameEnd();
        }

        BeforeShutdown();

        return KIWI_EXIT_SUCCESS;
    }

    void Application::Stop() {
        // m_isRunning.store(false, MEM_ORDER_SEQ_CST);
    }
}

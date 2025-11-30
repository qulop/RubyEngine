#include "EngineConfig.hpp"
#include "Application.hpp"


#include <renderer/shaders/ShaderCacheManager.hpp>
#include <types/Logger.hpp>
#include <sync/Atomic.hpp>
#include <utility/Time.hpp>
#include <events/EventManager.hpp>
#include <profiler/EngineProfiler.hpp>
#include <core/Object.hpp>



namespace Ruby {
    Path Application::s_applicationOutputDirectory = Path{};


    Path Application::GetApplicationOutputDirectory() {
        RUBY_ASSERT_BASIC(!s_applicationOutputDirectory.empty());

        return s_applicationOutputDirectory;
    }

    bool Application::Init() {
    #ifdef RUBY_DEBUG_BUILD
        if (!Platform::CreateDebugConsole()) {
            return false;
        }
    #endif

        s_subsystems = RUBY_NOTHROW_NEW SubsystemHolderType();
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

        Logger::Init(GetApplicationOutputDirectory());

        // TODO: Replace ShaderCacheManager with the `CacheManager`
        RUBY_IGNORE_RETURN(ShaderCacheManager::Init());

        RegisterSubsystem(RUBY_NOTHROW_NEW EventSubsystem);

        m_engine = MakeShared<Engine>();
        if (!m_engine->Init(m_cliOptions)) {
            RUBY_ERROR("Application::Init() : Failed to initialize the engine instance");
            return false;
        }

        m_isInitialized.store(true);
        return true;
    }

    void Application::BeforeShutdown() {
        delete s_subsystems;
    }

    i32 Application::Run() {
        RUBY_ASSERT(m_isInitialized.load(), "You must initialize an application first");

        BeforeRun();

        while (true) {

            this->Update();

            if (!m_engine->Update()) {
                break;
            }
        }

        BeforeShutdown();

        return RUBY_EXIT_SUCCESS;
    }

    void Application::Stop() {
        // m_isRunning.store(false, MEM_ORDER_SEQ_CST);
    }
}
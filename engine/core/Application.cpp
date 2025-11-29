#include "EngineConfig.hpp"
#include "Application.hpp"


#include <renderer/shaders/ShaderCacheManager.hpp>
#include <types/Logger.hpp>
#include <sync/Atomic.hpp>
#include <utility/Time.hpp>
#include <events/EventManager.hpp>
#include <profiler/EngineProfiler.hpp>



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

        EventManager::Init();

        m_engine = MakeShared<Engine>();
        if (!m_engine->Init(m_cliOptions)) {
            RUBY_ERROR("Application::Init() : Failed to initialize the engine instance");
            return false;
        }

        return true;
    }

    i32 Application::Run() {
        // TODO: Should we add here an assertion to prevent call before initialization?

        while (true) {

            this->Update();

            if (!m_engine->Update()) {
                break;
            }
        }

        return RUBY_EXIT_SUCCESS;
    }

    void Application::Stop() {
        // m_isRunning.store(false, MEM_ORDER_SEQ_CST);
    }
}
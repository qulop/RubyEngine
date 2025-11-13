#include "EngineConfig.hpp"
#include "Application.hpp"


#include <renderer/shaders/ShaderCacheManager.hpp>
#include <types/Logger.hpp>
#include <sync/Atomic.hpp>
#include <utility/Time.hpp>
#include <events/EventManager.hpp>



namespace Ruby {
    bool Application::Init() {
        m_cliOptions = ProgramOptions::Parse(Platform::GetApplicationArguments()).value_or(ProgramOptions());
        if (m_cliOptions.IsEmpty()) {
            Console::WriteLine("Failed to parse command line arguments");
            return false;
        }

        // TODO: Replace ShaderCacheManager with the `CacheManager`
        RUBY_IGNORE_RETURN(ShaderCacheManager::Init());

        EventManager::Init();

        return true;
    }

    i32 Application::Run() {
        // TODO: Should we add here an assertion to prevent call before initialization?

        while (m_isRunning.load(MEM_ORDER_RELAXED)) {
            Time::UpdateTime();

            m_window->PollEvents();
            if (!m_window->Update()) {
                Stop();
            }

            this->Update();
        }

        return RUBY_EXIT_SUCCESS;
    }

    void Application::Stop() {
        m_isRunning.store(false, MEM_ORDER_SEQ_CST);
    }
}
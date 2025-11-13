#pragma once

#include <utility/Definitions.hpp>
#include <misc/IWindow.hpp>
#include <core/EngineConfig.hpp>



namespace Ruby {
    class RUBY_API Application  {
    public:
        RUBY_NODISCARD virtual bool Init();

        RUBY_NODISCARD i32 Run();
        virtual void Stop();
        virtual void Update() {}

        virtual ~Application() = default;

    private:
        SharedPtr<IWindow> m_window;

        ProgramOptions m_cliOptions;
        EngineConfig m_engineConfig;

        std::atomic<bool> m_isRunning = true;
    };
}
#pragma once

#include <utility/Definitions.hpp>
#include <misc/Window.hpp>

#include <core/EngineConfig.hpp>
#include <core/Engine.hpp>
#include <core/Object.hpp>



namespace Ruby {
    class RUBY_API Application : public AObject {
        RUBY_CREATE_OBJECT(Application)

    public:
        RUBY_NODISCARD static Path GetApplicationOutputDirectory();

    public:
        RUBY_NODISCARD virtual bool Init();

        virtual void BeforeRun() {}
        virtual void BeforeShutdown();

        RUBY_NODISCARD i32 Run();
        virtual void Stop();
        virtual void Update() {}

        ~Application() override = default;

    private:
        std::atomic<bool> m_isInitialized = false;

        static Path s_applicationOutputDirectory;

        SharedPtr<Engine> m_engine;

        ProgramOptions m_cliOptions;
    };
}

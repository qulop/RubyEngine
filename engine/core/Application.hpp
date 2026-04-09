#pragma once

#include <common/Definitions.hpp>
#include <common/ProgramOptions.hpp>
#include <misc/Window.hpp>

#include <core/EngineConfig.hpp>
#include <core/Engine.hpp>
#include <core/Object.hpp>



namespace Kiwi {
    class KIWI_API Application : public AObject {
        KIWI_CREATE_OBJECT(Application, AObject)

    public:
        KIWI_NODISCARD static Path GetApplicationOutputDirectory();

    public:
        KIWI_NODISCARD virtual bool Init();

        virtual void BeforeRun() {}
        virtual void BeforeShutdown();

        virtual void BeforeFrameBegin() {}
        virtual void BeforeFrameEnd() {}

        KIWI_NODISCARD i32 Run();
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

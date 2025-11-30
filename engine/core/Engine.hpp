#pragma once

#include <utility/ProgramOptions.hpp>

#include <renderer/Renderer.hpp>

#include <core/EngineConfig.hpp>
#include <core/Object.hpp>

#include <misc/Window.hpp>



namespace Ruby {
    class Engine final : public AObject {
        RUBY_CREATE_OBJECT(Engine)

    public:
        RUBY_NODISCARD bool Init(const ProgramOptions& opts);

        RUBY_NODISCARD bool Update();

        RUBY_NODISCARD bool IsRunning() const;

        ~Engine() override = default;

    private:
        RUBY_NODISCARD bool CreateMainWindow(StringView windowName);

        RUBY_NODISCARD String GetDefaultWindowName() const;

    private:
        SharedPtr<AWindow> m_window;
        SharedPtr<Renderer> m_renderer;

        EngineConfig m_engineConfig;

        std::atomic<bool> m_isRunning = true;

        bool m_vsyncEnable = true;
        u16 m_fpsLimit = 120;
    };
}
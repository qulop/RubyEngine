#pragma once

#include <utility/ProgramOptions.hpp>

#include <renderer/Renderer.hpp>

#include <core/EngineConfig.hpp>
#include <core/Object.hpp>

#include <misc/Window.hpp>

#include <sync/Atomic.hpp>


namespace Kiwi {
    class Engine final : public AObject {
        KIWI_CREATE_OBJECT(Engine)

    public:
        KIWI_NODISCARD bool Init(const ProgramOptions& opts);

        KIWI_NODISCARD bool Update();

        KIWI_NODISCARD bool IsRunning() const;

        ~Engine() override = default;

    private:
        SharedPtr<AWindow> m_window;
        SharedPtr<Renderer> m_renderer;

        EngineConfig m_engineConfig;

        Atomic<bool> m_isRunning = true;

        bool m_vsyncEnable = true;
        u16 m_fpsLimit = 120;
    };
}

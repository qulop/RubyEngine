#include "Engine.hpp"

#include <core/EngineConfig.hpp>

#include <platform/window/GLFWWindow.hpp>

#include <profiler/EngineProfiler.hpp>


namespace Ruby {
    bool Engine::Init(const ProgramOptions& opts) {
        m_vsyncEnable = opts.Get<bool>(OPT_VSYNC_ENABLE).value_or(m_vsyncEnable);

        auto windowName = opts.Get<String>(OPT_WINDOW_NAME).value_or(GetDefaultWindowName());
        if (!CreateMainWindow(windowName)) {
            return false;
        }

        m_renderer = MakeShared<Renderer>();
        if (!m_renderer->Init()) {
            RUBY_ERROR("Engine::Init() : Failed to initialize the renderer");
            return false;
        }

        return true;
    }

    bool Engine::Update() {
        RUBY_PROFILE_ZONE_NAME("Engine::Update");

        m_window->PollEvents();
    }

    bool Engine::IsRunning() const {
        return m_isRunning.load();
    }

    bool Engine::CreateMainWindow(StringView windowName) {
        Vector<Platform::DisplayInfo> displayInfos = Platform::EnumerateDisplays();
        if (displayInfos.empty()) {
            RUBY_ERROR("Engine::CreateMainWindow() : Failed to enumerate system displays");
            return false;
        }

        auto selectedDisplay = std::ranges::find_if(displayInfos, [](const auto& displayInfo) {
            return Platform::IsDisplayCurrentlyActive(displayInfo);
        });
        if (selectedDisplay == displayInfos.end()) {
            RUBY_WARNING("Engine::CreateMainWindow() : Failed to find a preferred display to use. We will use the first one found earlier");
            selectedDisplay = displayInfos.begin();
        }

        RUBY_INFO("Engine::CreateMainWindow() : Selected display: {} - {} with resolution {}x{} and refresh rate {}Hz",
            selectedDisplay->model, selectedDisplay->name, selectedDisplay->resolution.x, selectedDisplay->resolution.y,
            selectedDisplay->refreshRate
        );

        m_window = AWindow::CreateWindowImpl();
        if (!m_window->Init(windowName, *selectedDisplay)) {
            return false;
        }
        m_window->SetVSyncEnable(m_vsyncEnable);
        m_window->MaximizeWindow(true);

        return true;
    }

    // Placeholder at this moment
    String Engine::GetDefaultWindowName() const {
        return "Ruby Engine";
    }
}

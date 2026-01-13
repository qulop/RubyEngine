#include "WindowSubsystem.hpp"


namespace Kiwi {
    bool WindowSubsystem::Init() {
        Super::Init();

        return true;
    }

    bool WindowSubsystem::CreateMainWindow(StringView title) {
        KIWI_ASSERT(!m_mainWindow, "Main window already created!");

        Vector<Platform::DisplayInfo> displayInfos = Platform::EnumerateDisplays();
        if (displayInfos.empty()) {
            KIWI_CTX_LOG(ERROR, "Failed to enumerate system displays");
            return false;
        }

        auto selectedDisplay = std::ranges::find_if(displayInfos, [](const auto& displayInfo) {
            return Platform::IsDisplayCurrentlyActive(displayInfo);
        });
        if (selectedDisplay == displayInfos.end()) {
            KIWI_CTX_LOG(WARNING, "Failed to find a preferred display to use. We will use the first one found earlier");
            selectedDisplay = displayInfos.begin();
        }

        KIWI_CTX_LOG(INFO, "Selected display: {} - {} with resolution {}x{} and refresh rate {}Hz",
            selectedDisplay->model,
            selectedDisplay->name,
            selectedDisplay->resolution.x,
            selectedDisplay->resolution.y,
            selectedDisplay->refreshRate
        );

        m_mainWindow = AWindow::CreateWindowImpl();
        if (!m_mainWindow->Init(title, *selectedDisplay)) {
            return false;
        }

        return true;
    }

    SharedPtr<AWindow> WindowSubsystem::GetMainWindow() {
        KIWI_ENSURE(m_mainWindow);

        return m_mainWindow;
    }

    Vector<const char*> WindowSubsystem::GetVulkanExtensionsForWindow(SharedPtr<AWindow> window) {
        KIWI_ENSURE(window);

        return window->GetVulkanExtensions();
    }
}

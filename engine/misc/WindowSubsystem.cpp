#include "WindowSubsystem.hpp"


namespace Kiwi {
    SharedPtr<AWindow> WindowSubsystem::GetMainWindow() {
        return m_mainWindow;
    }

    Vector<const char*> WindowSubsystem::GetVulkanExtensionsForWindow(SharedPtr<AWindow> window) {
        KIWI_ASSERT_BASIC(window);

        return window->GetVulkanExtensions();
    }
}

#pragma once

#include <core/Object.hpp>

#include <misc/Window.hpp>


namespace Kiwi {
    class WindowSubsystem : public ASubsystem {
        KIWI_CREATE_OBJECT(WindowSubsystem, ASubsystem)

    public:
        bool Init() override;
        KIWI_NODISCARD bool CreateMainWindow(StringView title);

        KIWI_NODISCARD SharedPtr<AWindow> GetMainWindow();

        KIWI_NODISCARD Vector<const char*> GetVulkanExtensionsForWindow(SharedPtr<AWindow> window);



    private:
        SharedPtr<AWindow> m_mainWindow;
    };
}
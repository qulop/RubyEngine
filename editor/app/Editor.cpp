#include "Editor.hpp"

#include <gui/ImGuiSubsystem.hpp>

#include <misc/WindowSubsystem.hpp>



namespace Kiwi::Editor {
    bool Editor::Init() {
        if (!Super::Init()) {
            return false;
        }

        RegisterSubsystem<ImGuiSubsystem>();
        auto imGuiSubsystem = GetSubsystem<ImGuiSubsystem>();
        if (!imGuiSubsystem->Init()) {
            return false;
        }



    }

}


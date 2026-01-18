#include "ImGuiSubsystem.hpp"

#include <misc/WindowSubsystem.hpp>

#include <imgui.h>



namespace Kiwi::Editor {
    bool ImGuiSubsystem::Init() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        ImGui::StyleColorsDark();

        auto mainWindow = GetSubsystem<WindowSubsystem>()->GetMainWindow();

        return true;
    }

}
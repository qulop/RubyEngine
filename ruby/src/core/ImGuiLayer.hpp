#pragma once

#include "Layer.hpp"
#include "IWindow.hpp"


namespace Ruby {
    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnEvent(IEvent* event) override;
        void Update() override;

        ~ImGuiLayer() override = default;
    };
}
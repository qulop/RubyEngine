#pragma once

#include <core/Object.hpp>

#include <renderer/pipeline/GraphicAPI.hpp>

#include <types/Errors.hpp>



namespace Kiwi {
    KIWI_FORWARD_DECLARATIONS(
        KIWI_ABSTRACT class AWindow;
    )
}

namespace Kiwi::Editor {
    template<EGraphicAPI API>
    struct InitImGuiForAPI;


    class ImGuiSubsystem : public ASubsystem {
    public:
        ImGuiSubsystem() = default;

    public:
        KIWI_NODISCARD bool Init() override;

    };
}
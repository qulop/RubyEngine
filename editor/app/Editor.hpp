#pragma once

#include <core/Application.hpp>


namespace Kiwi::Editor {
    class Editor : public Application {
    public:
        using Super = Application;

    public:
        KIWI_NODISCARD bool Init() override;


    };
}
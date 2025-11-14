#pragma once

#include <utility/ProgramOptions.hpp>

#include <core/EngineConfig.hpp>

#include <misc/IWindow.hpp>


namespace Ruby {
    class Engine {
    public:
        RUBY_NODISCARD bool Init(const ProgramOptions& opts);

        RUBY_NODISCARD bool Update();

    private:
        RUBY_NODISCARD bool CreateMainWindow(StringView windowName);

        RUBY_NODISCARD String GetDefaultWindowName() const;

    private:
        SharedPtr<IWindow> m_window;

        EngineConfig m_engineConfig;

        bool m_vsyncEnable = true;
        u16 m_fpsLimit = 120;


    };
}
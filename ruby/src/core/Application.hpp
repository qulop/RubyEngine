#pragma once

#include <utility/Definitions.hpp>
#include <utility/CommandLIneArgs.hpp>
#include "LayersStack.hpp"
#include "Layer.hpp"
#include "IWindow.hpp"


namespace Ruby {
    class RUBY_API Application {
    public:
        Application();
        Application(CommandLineArgs args, VideoStruct va);

        RUBY_NODISCARD bool IsInitialized() const;

        void Start();
        void Finish();

        void PushBottomLayer(Layer* layer);
        void PushTopLayer(Layer* layer);

        RUBY_NODISCARD const CommandLineArgs& GetLaunchArgs() const;
        RUBY_NODISCARD const Ptr<IWindow>& GetWindow() const;

        virtual ~Application() = default;

    private:
        LayersStack m_layers;
        CommandLineArgs m_args;
        Ptr<IWindow> m_window;  // I still think that std::unique_ptr needed here

        std::atomic<bool> m_isInitialized = false;
        std::atomic<bool> m_isRunning = true;
    };
}
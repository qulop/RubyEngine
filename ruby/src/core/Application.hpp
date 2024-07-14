#pragma once

#include <utility/Definitions.hpp>
#include <utility/CommandLineArgs.hpp>
#include "LayersStack.hpp"
#include "Layer.hpp"
#include "IWindow.hpp"


namespace Ruby
{
    class RUBY_API Application {
    public:
        Application();
        Application(CommandLineArgs args, VideoStruct va);

        u8 Start();
        void Finish();

        void PushBottomLayer(Layer* layer);
        void PushBottomLayer(Ptr<Layer> layer); // moving Ptr

        void PushTopLayer(Layer* layer);
        void PushTopLayer(Ptr<Layer> layer); // moving Ptr

        RUBY_NODISCARD const CommandLineArgs& GetLaunchArgs() const;
        RUBY_NODISCARD const Ptr<IWindow>& GetWindow() const;

        virtual ~Application() = default;

    private:
        LayersStack m_layers;
        CommandLineArgs m_args;
        Ptr<IWindow> m_window;  // I still think that std::unique_ptr needed here

        bool m_isRunning = true;
    };
}
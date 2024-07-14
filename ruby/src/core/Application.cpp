#include "Application.hpp"
#include "Timer.hpp"


namespace Ruby {
    Application::Application() {
        Logger::GetInstance().Init();
    }

    Application::Application(CommandLineArgs args, VideoStruct va) :
        Application()
    {
        m_args = std::move(args);
        m_window = IWindow::Create(std::move(va));
    }

    u8 Application::Start() {
        auto lastTime = Time::getCurrentTimeRep();
        Time::TimeRep accumulator = 0;

        while (m_isRunning) {
            auto currentTime = Time::getCurrentTimeRep();
            auto deltaTime = currentTime - lastTime;

            m_window->PollEvents();

            // Starting from the top layers
            auto layersIt = std::rbegin(m_layers);
            for (layersIt; layersIt != std::rend(m_layers); layersIt++) {
                auto layer = *layersIt;
                layer->Update();
            }

            if (m_window->Update())
                Finish();

            lastTime = currentTime;
        }

        return 0;
    }

    void Application::Finish() {
        m_isRunning = false;
    }

    void Application::PushBottomLayer(Layer* layer) {
        m_layers.PushBottomLayer(layer);
    }

    void Application::PushBottomLayer(Ptr<Ruby::Layer> layer) {
        m_layers.PushBottomLayer(std::move(layer));
    }

    void Application::PushTopLayer(Layer* layer) {
        m_layers.PushTopLayer(layer);
    }

    void Application::PushTopLayer(Ptr<Layer> layer) {
        m_layers.PushTopLayer(std::move(layer));
    }

    const CommandLineArgs& Application::GetLaunchArgs() const {
        return m_args;
    }

    const Ptr<IWindow>& Application::GetWindow() const {
        return m_window;
    }
}
#include <renderer/Renderer.hpp>
#include <platform/Platform.hpp>
#include <types/Logger.hpp>
#include <utility/Assert.hpp>

#include "EngineGlobalConfig.hpp"
#include "Application.hpp"
#include "Timer.hpp"


namespace Ruby {
    void Application::InitEngine(ProgramOptions&& opts) {
        auto& globalConfig = EngineGlobalConfig::GetInstance();
        globalConfig.Init(std::move(opts));

        Logger::GetInstance().InitLogger(globalConfig.loggerBaseDirectory);

        m_window = IWindow::Create(globalConfig.videoConfig);

        Renderer::Init();
        RUBY_SWITCH_BOOL(m_isInitialized);
    }

    
    bool Application::IsInitialized() const {
        return m_isInitialized;
    }


    void Application::Start() {
        RUBY_ASSERT(m_isInitialized, "Application must be initialized before launch!");

        auto lastTime = Time::getCurrentTimeRep();
        Time::TimeRep accumulator = 0;

        while (m_isRunning) {
            auto currentTime = Time::getCurrentTimeRep();
            auto deltaTime = currentTime - lastTime;

            m_window->PollEvents();

            // Starts from top layers
            auto layersIt = std::rbegin(m_layers);
            for (layersIt; layersIt != std::rend(m_layers); layersIt++) {
                auto layer = *layersIt;
                layer->Update();
            }

            if (!m_window->Update())
                Finish();

            lastTime = currentTime;
        }
    }

    void Application::Finish() {
        m_isRunning = false;
    }

    void Application::PushBottomLayer(Layer* layer) {
        m_layers.PushBottomLayer(layer);
    }

    void Application::PushTopLayer(Layer* layer) {
        m_layers.PushTopLayer(layer);
    }

    const Ptr<IWindow>& Application::GetWindow() const {
        return m_window;
    }
}
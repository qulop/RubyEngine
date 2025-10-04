#include "EngineGlobalConfig.hpp"
#include "Application.hpp"
#include "Editor.hpp"

#include <renderer/Renderer2D.hpp>
#include <renderer/shaders/ShaderCacheManager.hpp>
#include <types/Logger.hpp>
#include <sync/Atomic.hpp>
#include <types/Timer.hpp>
#include <utility/Assert.hpp>
#include <events/EventManager.hpp>



namespace Ruby {
    void Application::InitApplication(ProgramOptions&& opts) {
        auto& globalConfig = Globals::globalConfig;
        globalConfig.InitFromCommandLine(std::move(opts));

        Logger::Init(globalConfig.loggerBaseDirectory);
        m_window = IWindow::Create(globalConfig.videoConfig);

        (void)ShaderCacheManager::Init();   // TODO: Should we remove this and move it in something like `GlobalCacheManager::InitUnderlyingManagers()`?
        
        EventManager::Init();
        Renderer2D::Init(globalConfig.videoConfig.width, globalConfig.videoConfig.height);

        m_isInitialized.exchange(true, MEM_ORDER_RELAXED);
    }

    bool Application::IsInitialized() const {
        return m_isInitialized.load(MEM_ORDER_RELAXED);
    }

    void Application::StartApplication() {
        RUBY_ASSERT(m_isInitialized.load(MEM_ORDER_RELAXED), 
            "You cannot start uninitialized application!");

        auto lastTime = Time::getCurrentTimeRep();
        Time::TimeRep accumulator = 0;

        while (m_isRunning.load(MEM_ORDER_RELAXED)) {
            auto& a = EventManager::GetInstance();

            auto currentTime = Time::getCurrentTimeRep();
            auto deltaTime = currentTime - lastTime;

            m_window->PollEvents();

            // If `m_layers` on MSVC is empty,
            // then it STL-assert will occured("cannot decrement begin list iterator")
            // (if _ITERATOR_DEBUG_LEVEL macro setted to 2)
            if (m_layers.Size() != 0) {
                for (auto layerIt = m_layers.rbegin(); layerIt != m_layers.rend(); ++layerIt)
                    (*layerIt)->Update();
            }

            if (!m_window->Update())
                Finish();

            lastTime = currentTime;
        }
    }

    void Application::Finish() {
        m_isRunning.store(false, MEM_ORDER_SEQ_CST);
    }

    void Application::PushBottomLayer(ALayer* layer) {
        m_layers.PushBottomLayer(layer);
    }

    void Application::PushTopLayer(ALayer* layer) {
        m_layers.PushTopLayer(layer);
    }

    const SharedPtr<IWindow>& Application::GetWindow() const {
        return m_window;
    }
}
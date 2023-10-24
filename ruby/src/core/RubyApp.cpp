#include "RubyApp.hpp"


namespace Ruby
{

    RubyApp::RubyApp(void) 
    {
        Logger::Init();

        auto& mng = EventManager::Get();

        std::function<void(MouseMoveEvent&)> func = onEvent;
        std::cout << mng.AddListener(EventType::MOUSE_MOVED_EVENT, func) << std::endl;
    }


    RubyApp::RubyApp(WindowAttributes& winAttr) :
        RubyApp()
    {
        m_window = std::make_unique<Window>(winAttr);
    }


    uint8_t RubyApp::Mainloop(void) 
    {
        double currentTime = 0;
        while(m_isRunning)
        {
            m_window->Update();
        }

        return 0;
    }

    
    void RubyApp::Finish(void) 
    {
        m_isRunning = false;
    }

    RubyApp::~RubyApp(void)
    {}

}
#include "RubyApp.hpp"


namespace Ruby
{

    RubyApp::RubyApp(void) 
    {
        initCoreLogger("logs/log-from.txt");  // it's should looks like log-from_21-11-2023.txt
    }


    RubyApp::RubyApp(VideoAttr& va) :
        RubyApp()
    {
        m_window = std::make_unique<Window>(va);
    }


    uint8_t RubyApp::Mainloop(void) 
    {
        double lastTime = 0;
        while(0)
        {
            double currentTime = 0;
            double deltaTime = lastTime - currentTime;
        
            Update(deltaTime);
            if (!m_window->Update())
                break;

            lastTime = currentTime;
        }

        return 0;
    }

    
    void RubyApp::Finish(void) 
    {
        m_isRunning = false;
    }


    void RubyApp::SetFramerate(uint16_t newFramerate)
    {
        RUBY_ASSERT(m_isRunning == false && "You cannot set new framerate after starting the application!");

        m_framerate = newFramerate;
    }


    RubyApp::~RubyApp(void)
    {}

}
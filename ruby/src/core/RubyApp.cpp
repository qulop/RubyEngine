#include "RubyApp.hpp"


namespace Ruby
{

    RubyApp::RubyApp(void) 
    {
        initCoreLogger("logFrom.txt");  // it's should looks like logFrom_21_11_2023.txt
    }


    RubyApp::RubyApp(VideoAttr& va) :
        RubyApp()
    {
        m_window = std::make_unique<Window>(va);     
    }


    uint8_t RubyApp::Mainloop(void) 
    {
        RUBY_INFO("Mainloop() start");


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

        RUBY_CRITICAL("Mainloop() end: {}", lastTime);

        return 0;
    }

    
    void RubyApp::Finish(void) 
    {
        m_isRunning = false;
    }


    RubyApp::~RubyApp(void)
    {}

}
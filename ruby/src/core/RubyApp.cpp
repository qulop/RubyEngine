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
        auto lastTime = RubyTime::getCurrentTimeRep();
        RubyTime::TimeRep accumulator = 0;

        while(m_isRunning)
        {
            auto currentTime = RubyTime::getCurrentTimeRep();
            auto deltaTime = currentTime - lastTime;
            accumulator += deltaTime;

            m_window->PollEvents();
        
            while (accumulator >= rubySettings.GetTimestep())
            {
                this->Update();
                accumulator -= std::min(deltaTime, rubySettings.GetTimestep());
            }

            if (!m_window->Update())
                break;

            lastTime = currentTime;

            if (auto fps = GetFPS())
                fprintf_s(stdout, "FPS: %d\n", fps);
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

        rubySettings.SetMaxFPS(newFramerate);
    }


    RubyApp::~RubyApp(void)
    {}


// private
    uint16_t RubyApp::GetFPS(void)
    {
        static RubyTime::SteadyTimePoint lastTime = RubyTime::time::steady_clock::now();
        static uint16_t fps = 0;
        fps++;

        RubyTime::SteadyTimePoint currentTime = RubyTime::time::steady_clock::now();

        if (RubyTime::time::duration_cast<RubyTime::time::seconds>(currentTime - lastTime) >= RubyTime::time::seconds{ 1 })
        {
            lastTime = currentTime;
            auto tmp = fps;
            fps = 0;
            return tmp;
        }

        return 0;
    }
}
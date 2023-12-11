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
        printf_s("1\n");

        while(m_isRunning)
        {
            auto currentTime = RubyTime::getCurrentTimeRep();
            auto deltaTime = currentTime - lastTime;
            accumulator += deltaTime;
            printf_s("2\n");

            m_window->PollEvents();
            printf_s("3\n");
        
            while (accumulator >= rubySettings.GetTimestep())
            {
                printf_s("4\n");
                this->Update();
                accumulator -= deltaTime;
                printf_s("5\n");
            }

            if (!m_window->Update())
                break;

            printf_s("6\n");
            lastTime = currentTime;

            if (auto fps = GetFPS())
                fprintf_s(stdout, "FPS: %d", fps);
            printf_s("7\n");
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
        static RubyTime::SteadyTimePoint lastTime = RubyTime::steady_clock::now();
        static uint16_t fps = 0;
        fps++;

        RubyTime::SteadyTimePoint currentTime = RubyTime::steady_clock::now();

        if (RubyTime::duration_cast<RubyTime::seconds>(currentTime - lastTime) >= RubyTime::seconds{ 1 })
        {
            lastTime = currentTime;
            return fps;
        }

        return FPS_NOT_CALCULATED;
    }

}
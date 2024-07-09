#include <core/RubyApp.hpp>


namespace Ruby
{

    RubyApp::RubyApp()
    { Logger::GetInstance().Init(); }


    RubyApp::RubyApp(const VideoStruct& va) :
        RubyApp()
    {
        m_window = IWindow::Create(va).get();
    }


    u8 RubyApp::Mainloop()
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
                RUBY_INFO("FPS: {}", fps);
        }

        return 0;
    }

    
    void RubyApp::Finish()
    {
        m_isRunning = false;
    }


    void RubyApp::SetFramerate(u8 newFramerate)
    {
        RUBY_ASSERT(m_isRunning == false, "You cannot set new framerate after starting the application!");

        rubySettings.SetMaxFPS(newFramerate);
    }


    u16 RubyApp::GetFPS()
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
#include "RubyApp.hpp"


namespace Ruby
{
    uint16_t EngineSettingsStruct::GetMaxFPS(void) const
    {
        return m_maxFPS;
    }

    float EngineSettingsStruct::GetTimestep(void) const
    {
        return m_timestep;
    }


    void EngineSettingsStruct::SetMaxFPS(uint16_t fps)
    {
        RUBY_WARNING("maxFPS changed from {} to {}(timestep also changed from {} to {})", 
                        m_maxFPS, fps, m_timestep, 1000 / fps);

        m_maxFPS = fps;
        m_timestep = static_cast<float>(1000 / m_maxFPS);
    }



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
                if (!m_window->Update())
                    break;
                accumulator -= (deltaTime < rubySettings.GetTimestep()) ? deltaTime : rubySettings.GetTimestep();
            }

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

        rubySettings.SetMaxFPS(newFramerate);
    }


    RubyApp::~RubyApp(void)
    {}

}
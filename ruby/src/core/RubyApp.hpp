#pragma once

#include <utility/Definitions.hpp>
#include <utility/Logger.hpp>
#include "Window.hpp"
#include "Timer.hpp"
#include <iostream>

namespace Ruby
{
    struct EngineSettingsStruct
    {
    private:
        uint16_t m_maxFPS = 120;
        float m_timestep = 1000 / m_maxFPS;

    public:
        uint16_t GetMaxFPS(void) const;

        float GetTimestep(void) const;

        void SetMaxFPS(uint16_t fps);

    } rubySettings;




    class RUBY_API RubyApp
    {
    protected:
        RubyApp(void);
        
        RubyApp(VideoAttr& va);

    public:
        uint8_t Mainloop(void);

        void Finish(void);

        virtual void Update(void) = 0;

        void SetFramerate(uint16_t newFramerate);

        virtual ~RubyApp(void);

    private:
        std::unique_ptr<Window> m_window;

        bool m_isRunning = true;
    };

}
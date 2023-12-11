#pragma once

#include <utility/Definitions.hpp>
#include <utility/Logger.hpp>
#include "EngineSettings.hpp"
#include "Window.hpp"
#include "Timer.hpp"

#include <iostream>


#define FPS_NOT_CALCULATED   0


namespace Ruby
{
    class RUBY_API RubyApp
    {
    protected:
        RubyApp(void);
        
        RubyApp(VideoAttr& va);

    protected:
        EngineSettingsStruct rubySettings;

    public:
        uint8_t Mainloop(void);

        void Finish(void);

        virtual void Update(void) = 0;

        void SetFramerate(uint16_t newFramerate);

        virtual ~RubyApp(void);

    private:
        uint16_t GetFPS(void);

    private:
        std::unique_ptr<Window> m_window;

        bool m_isRunning = true; 
    };

}
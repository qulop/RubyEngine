#pragma once

#include <utility/Definitions.hpp>
#include <utility/Logger.hpp>
#include "EngineSettings.hpp"
#include "Window.hpp"
#include "Timer.hpp"

#include <algorithm>
#include <iostream>


namespace Ruby
{
    class RUBY_API RubyApp
    {
    protected:
        RubyApp(void);
        
        explicit RubyApp(VideoAttr& va);

    protected:
        EngineSettingsStruct rubySettings;

    public:
        u8 Mainloop(void);

        void Finish(void);

        virtual void Update(void) = 0;

        void SetFramerate(u8 newFramerate);

        virtual ~RubyApp(void);

    private:
        u16 GetFPS(void);

    private:
        std::unique_ptr<Window> m_window;
        bool m_isRunning = true; 
    };

}
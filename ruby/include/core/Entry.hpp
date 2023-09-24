#pragma once

#include "Core.hpp"
#include "Logger.hpp"
#include "Window.hpp"

namespace Ruby
{

    class RUBY_API RubyApp
    {
    public:

        RubyApp(void);
        
        RubyApp(WindowAttributes& winAttr);

        uint8_t Run(void);

        virtual void Update(void) = 0;

        void Stop(void);

        virtual ~RubyApp(void);

    private:
        std::unique_ptr<Window> m_window;
        bool m_isRunning = true;
    };

}
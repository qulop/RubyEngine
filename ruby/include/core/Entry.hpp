#pragma once

#include "Core.hpp"
#include "Window.hpp"
#include <cstdio>

namespace Ruby
{

    class RUBY_API RubyApp
    {
    public:

        RubyApp(void);
        
        RubyApp(WindowAttrubutes& winAttr);

        uint8_t Run(void);

        void Stop(void);

        virtual ~RubyApp(void);

    private:
        Window* m_window;
        bool m_isRunning = true;
    };

}
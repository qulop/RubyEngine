#pragma once

#include "Core.hpp"
#include "Logger.hpp"
#include "Window.hpp"
#include <iostream>

namespace Ruby
{

    class RUBY_API RubyApp
    {
    protected:
        RubyApp(void);
        
        RubyApp(VideoAttr& va);

    public:
        uint8_t Mainloop(void);

        void Finish(void);

        virtual void Update(double deltaTime) = 0;

        virtual ~RubyApp(void);

    private:
        std::unique_ptr<Window> m_window;
        bool m_isRunning = true;
    };

}
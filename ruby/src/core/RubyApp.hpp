#pragma once

#include "Core.hpp"
#include "Logger.hpp"
#include "Window.hpp"
#include <iostream>

namespace Ruby
{

    void onEvent(MouseMoveEvent& event)
    {
        std::cout << "X: " << event.GetX() << " Y: " << event.GetY() << std::endl;
    }



    class RUBY_API RubyApp
    {
    protected:
        RubyApp(void);
        
        RubyApp(WindowAttributes& winAttr);

    public:
        uint8_t Mainloop(void);

        void Finish(void);

        virtual ~RubyApp(void);

    private:
        std::unique_ptr<Window> m_window;
        bool m_isRunning = true;
    };

}
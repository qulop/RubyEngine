#include "RubyApp.hpp"


namespace Ruby
{

    RubyApp::RubyApp(void) 
    {
        Logger::Init();

    }


    RubyApp::RubyApp(VideoAttr& va) :
        RubyApp()
    {
        m_window = std::make_unique<Window>(va);

        auto sizes = m_window->GetRealSize();
        int x1 = (sizes.width / 2);
        int y1 = (sizes.height / 2) - 100;
        
        int x2 = (sizes.width / 2) - 100;
        int y2 = (sizes.height / 2) + 100;

        int x3 = (sizes.width / 2) + 100;
        int y3 = (sizes.height / 2) + 100;
        
        m_window->DrawTriangle({ x1, y2, x2, y2, x3, y3 });        
    }


    uint8_t RubyApp::Mainloop(void) 
    {
        double lastTime = 0;
        while(m_isRunning)
        {
            double currentTime = 0;
            double deltaTime = lastTime - currentTime;
        
            Update(deltaTime);
            if (!m_window->Update())
                break;

            lastTime = currentTime;
        }

        return 0;
    }

    
    void RubyApp::Finish(void) 
    {
        m_isRunning = false;
    }


    // void RubyApp::OnMouseEvent(MouseMoveEvent& event)
    // {
    //     int width, height;
    //     m_window->GetSize(width, height);

    //     int x1 = width - 100;
    //     int y1 = 0;

    //     int x2 = width;
    //     int y2 = 100;

    //     double x = event.GetX();
    //     double y = event.GetY();

    //     if ((x >= x1 && x <= x2) && (y >= y1 && y <= y2))
    //         std::cout << "Capy birthday Amy! I love u!" << std::endl;
    // }


    RubyApp::~RubyApp(void)
    {}

}
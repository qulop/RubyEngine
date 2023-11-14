#include "DemoApp.hpp"
#include <memory>


int main()
{
    Ruby::VideoAttr va { "Demo", 300, 300 };
    va.isResizable = false;

    std::unique_ptr<Demo> demoVn = std::make_unique<Demo>(va);
    auto errCode = demoVn->Mainloop();

    /*

        Ruby::Button btn;
        btn.addListener([](Ruby::Event& e)
        {
            if (e.GetX() == 100)
            {
                ... 
            }
        });


        void OnClick(Ruby::Event& event)
        {
            
        }

        Ruby::EventManager::AddListener(Ruby::MOUSE_PRESSED_EVENT, OnClick);


        auto/Event event = Ruby::IsHappened(Ruby::MOUSE_PRESSED_EVENT);
        if (event != Ruby::NONE_EVENT)
        {

        }
    */


    /*
        if (Ruby::eventHappened(Ruby::EventType::MOUSE))
    
    */

    if (!errCode)
    {
        Ruby::critical("Ruby::RubyApp::Mainloop() return error code: {}", errCode);
        return 1;
    }    
    return 0;
}
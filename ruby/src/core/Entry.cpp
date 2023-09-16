#include <core/Entry.hpp>


namespace Ruby
{

    RubyApp::RubyApp(void) 
    {}


    RubyApp::RubyApp(WindowAttrubutes& winAttr)
    {
        *m_window = Window{ winAttr };
    }


    uint8_t RubyApp::Run(void) 
    {
        // while(m_isRunning);
        m_window->showWindow();

        return RUBY_EXIT;
    }

    
    void RubyApp::Stop(void) 
    {
        m_isRunning = false;
    }

    RubyApp::~RubyApp(void)
    {}

}
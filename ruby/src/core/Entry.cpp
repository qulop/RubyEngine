#include <core/Entry.hpp>


namespace Ruby
{

    RubyApp::RubyApp(void) 
    {
        Logger::Init();
    }


    RubyApp::RubyApp(WindowAttributes& winAttr) :
        RubyApp()
    {
        m_window = std::make_unique<Window>(winAttr);
    }


    uint8_t RubyApp::Run(void) 
    {
        try
        {
            m_window->ShowWindow();
            
        }
        catch(...)
        {
            CORE_FLUSH();
        }
        
    
        return 0;
    }

    
    void RubyApp::Stop(void) 
    {
        m_isRunning = false;
    }

    RubyApp::~RubyApp(void)
    {}

}
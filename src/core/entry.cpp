#include "entry.hpp"


namespace Ruby
{

    uint8_t RubyApp::Run(void) const noexcept
    {
        if (!m_running)
            return RUBY_INIT_FAIL;

        while(m_running);

        return RUBY_EXIT;
    }

    
    void RubyApp::Stop(void) noexcept
    {
        m_running = false;
    }
}
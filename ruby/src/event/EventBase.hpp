#pragma once

#include <core/Core.hpp>
#include <core/Window.hpp>


/*

    Event e = isHappened(RB_MOUSE_PRESSED);

*/



namespace Ruby
{
    // "RB" mean Ruby :)
    enum EventType
    {
        RB_NONE_EVENT       = 0,
        RB_MOUSE_PRESSED    = (1 << 1),
        RB_MOUSE_RELEASED   = (1 << 2),
        RB_MOUSE_MOVED      = (1 << 3),
        RB_MOUSE_SCROLLED   = (1 << 4),
        RB_KEY_PRESSED      = (1 << 5),
        RB_KEY_RELEASED     = (1 << 6),
    };

    
    class RUBY_API Event
    {
    public:
        EventType GetType(void) const
        { return m_type; }

        std::weak_ptr<Window> ProviderWindow(void) const
        { return m_provider; } 

    protected:
        Event(EventType type, std::weak_ptr<Window>& provider) :
            m_type(type), m_provider(provider) 
        {}

    private:
        EventType m_type = RB_NONE_EVENT;
        std::weak_ptr<Window> m_provider;
    };
}


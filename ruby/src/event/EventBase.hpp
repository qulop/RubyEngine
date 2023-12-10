#pragma once

#include <utility/Definitions.hpp>
#include <core/Window.hpp>


namespace Ruby
{
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

    protected:
        Event(EventType type) :
            m_type(type) 
        {}

    private:
        EventType m_type = RB_NONE_EVENT;
    };
}


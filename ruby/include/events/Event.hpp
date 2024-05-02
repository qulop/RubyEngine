#pragma once

#include <utility/StdInc.hpp>
#include <utility/RubyUtility.hpp>


namespace Ruby
{
    RUBY_ENUM(EventType,
        RUBY_NONE_EVENT       = 0,
        RUBY_MOUSE_PRESSED    = (1 << 1),
        RUBY_MOUSE_RELEASED   = (1 << 2),
        RUBY_MOUSE_MOVED      = (1 << 3),
        RUBY_MOUSE_SCROLLED   = (1 << 4),
        RUBY_KEY_PRESSED      = (1 << 5),
        RUBY_KEY_RELEASED     = (1 << 6)
    )


    class IEvent
    {
    public:
        RUBY_NODISCARD virtual EventType GetType() const
        { return m_type; }

        RUBY_NODISCARD virtual RubyString ToString() const = 0;

        virtual ~IEvent() = default;

    protected:
        explicit IEvent(EventType type) :
            m_type(type)
        {}

        EventType m_type = RUBY_NONE_EVENT;
        EnumReflector m_reflector = EnumReflector::Create<EventType>();
    };
}
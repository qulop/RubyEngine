#pragma once

#include "Event.hpp"


namespace Ruby
{
    namespace Details::Events
    {
        class KeyboardEvent : public IEvent
        {
        public:
            RUBY_NODISCARD RubyString ToString() const override
            { return std::format("(EventID){} : key = {}, action = {}", static_cast<i32>(m_type), key, action); }

        public:
            const i32 key    = -1;
            const i32 action = -1;

        public:
            KeyboardEvent(i32 key, i32 action, EventType type) :
                IEvent(type),
                key(key),
                action(action)
            {}
        };
    }


    class KeyboardKeyPressed : public Details::Events::KeyboardEvent
    {
    public:
        KeyboardKeyPressed(i32 key, i32 action) :
            KeyboardEvent(key, action, RUBY_KEY_PRESSED)
        {}
    };


    class KeyboardKeyReleased : public Details::Events::KeyboardEvent
    {
    public:
        KeyboardKeyReleased(i32 key, i32 action) :
            KeyboardEvent(key, action, RUBY_KEY_RELEASED)
        {}
    };
}
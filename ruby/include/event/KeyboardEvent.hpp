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
            { return std::format("{} : key = {}, action = {}", m_type.GetFieldName(), key, action); }

        public:
            const i16 key    = -1;
            const i16 action = -1;

        protected: 
            KeyboardEvent(i16 key, i16 action, const ENUM_FIELD& type) :
                IEvent(type),
                key(key),
                action(action)
            {}
        };
    }


    class KeyboardKeyDown : public Details::Events::KeyboardEvent
    {
    public:
        KeyboardKeyDown(i16 key, i16 action) :
            KeyboardEvent(key, action, m_reflector.GetByKey("RUBY_KEY_PRESSED"))
        {}
    };


    class KeyboardKeyUp : public Details::Events::KeyboardEvent
    {
    public:
        KeyboardKeyUp(i16 key, i16 action) :
            KeyboardEvent(key, action, m_reflector.GetByKey("RUBY_KEY_RELEASED"))
        {}
    };
}
#pragma once

#include "IEvent.hpp"


namespace Ruby {
    namespace Details::Events {
        class _KeyboardEvent : public _EventBase {
        public:
            RUBY_NODISCARD RubyString ToString() const override {
                return std::format("{} : key = {}, action = {}",
                                   m_reflector.GetByValue(m_type).GetFieldName(),
                                   key,
                                   action);
            }

        public:
            const i32 key    = -1;
            const i32 action = -1;

        public:
            _KeyboardEvent(i32 key, i32 action, EventType type) :
                    _EventBase(type),
                    key(key),
                    action(action)
            {}
        };
    }


    class KeyboardKeyPressed : public Details::Events::_KeyboardEvent {
    public:
        KeyboardKeyPressed(i32 key, i32 action) :
            _KeyboardEvent(key, action, RUBY_KEY_PRESSED)
        {}
    };


    class KeyboardKeyReleased : public Details::Events::_KeyboardEvent {
    public:
        KeyboardKeyReleased(i32 key, i32 action) :
            _KeyboardEvent(key, action, RUBY_KEY_RELEASED)
        {}
    };
}
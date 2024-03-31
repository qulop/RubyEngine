#pragma once

#include "Event.hpp"
#include "Keys.hpp"

namespace Ruby
{
    namespace Details::Events
    {
        class KeyboardEvent : public Event
        {
        public:
            EventData GetData(void) const override
            { return { { "key", m_key }, { "action", m_action } }; }


        protected: 
            KeyboardEvent(int key, int action, EventType type) :
                Event(type),
                m_key(key),
                m_action(action)
            {}

        private:
            int m_key    = -1;
            int m_action = -1;
        };
    }


    class KeyboardKeyDown : public Details::Events::KeyboardEvent
    {
    public:
        KeyboardKeyDown(int key, int action) :
            KeyboardEvent(key, action, RB_KEY_PRESSED)
        {}
    };


    class KeyboardKeyUp : public Details::Events::KeyboardEvent
    {
    public:
        KeyboardKeyUp(int key, int action) :
            KeyboardEvent(key, action, RB_KEY_RELEASED)
        {}
    };

}
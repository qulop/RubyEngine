#pragma once

#include <any>
#include <utility/Definitions.hpp>


namespace Ruby
{
    namespace EventDetails
    {
        class EData
        {
        public:
            template<typename Tx>
            EData(Tx&& obj) :
                obj(std::forward<Tx>(obj)) 
            {}

            template<typename Tx>
            Tx Get(void) const
            { 
                if (!obj.has_value())
                    return 100;
                return std::any_cast<Tx>(obj); 
            }

        private:
            std::any obj;
        };
    }


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



    class Event
    {
    public:
        using EventData = RubyHashMap<RubyString, EventDetails::EData>;


        EventType GetType(void) const
        { return m_type; }

        // The use of this method is intended only in descendant classes 
        virtual EventData GetData(void) const
        { 
            RUBY_ASSERT(false && 
                "Failed to select correct method from Ruby::Event::_VTable. Perhaps you are calling a function/method with an Event passed by value?");

            return {};
        }

    protected:
        Event(EventType type) :
            m_type(type) 
        {}

    private:
        EventType m_type = RB_NONE_EVENT;
    };
}


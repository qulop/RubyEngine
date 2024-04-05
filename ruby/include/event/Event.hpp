#pragma once

#include <utility/StdInc.hpp>
#include <utility/Definitions.hpp>


namespace Ruby
{
    namespace Details::Events
    {
        class EData
        {
        public:
            template<typename Tx>
            EData(Tx&& obj) :
                m_obj(std::forward<Tx>(obj)) 
            {}

            template<typename Tx>
            Tx Get(void) const
            { return std::any_cast<Tx>(m_obj); }

        private:
            std::any m_obj;
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
        using EventData = RubyHashMap<RubyStringView, Details::Events::EData>;


        EventType GetType(void) const
        { return m_type; }

        // The use of this method is intended only in descendant classes 
        virtual EventData GetData(void) const
        { 
            RUBY_ASSERT(false, 
                "Failed to select correct method from Ruby::Event::_VTable. Perhaps you are calling a function/method with an Event passed by value?");

            return {};
        }

    protected:
        Event(EventType type) :
            m_type(type) 
        {}

    private:
        EventType m_type;
    };
}


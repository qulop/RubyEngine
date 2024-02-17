#include "Event.hpp"



namespace Ruby
{
    namespace MouseEventsDetails
    {
        // RB_MOUSE_PRESS && RB_MOUSE_RELEASED
        class MouseButtonAction : public Event
        {
        public:
            EventData GetData(void) const override
            { return { { "button", m_button } }; }

        protected:
            MouseButtonAction(int button, EventType type) :
                Event(type), 
                m_button(button) 
            {}

        private:
            int m_button = -1;    
        };


        // RB_MOUSE_MOVED && RB_MOUSE_SCROLLED
        class MouseStateAction : public Event
        {
        public:
            EventData GetData(void) const override
            { return { { "xoff", m_xoff }, { "yoff", m_yoff } }; }


        protected:
            MouseStateAction(double xoff, double yoff, EventType type) :
                Event(type), 
                m_xoff(xoff), 
                m_yoff(yoff) 
            {}

        private:
            double m_xoff = -1;
            double m_yoff = -1;
        };
    }



    class MousePressEvent : public MouseEventsDetails::MouseButtonAction
    {
    public:
        MousePressEvent(int button) :
                MouseButtonAction(button, RB_MOUSE_PRESSED) 
            {}
    };


    class MouseReleaseEvent : public MouseEventsDetails::MouseButtonAction
    {
    public:
        MouseReleaseEvent(int button) : 
                MouseButtonAction(button, RB_MOUSE_RELEASED)
            {}
    };

    class MouseMoveEvent : public MouseEventsDetails::MouseStateAction
    {
    public:
        MouseMoveEvent(double xoff, double yoff) :
                MouseStateAction(xoff, yoff, RB_MOUSE_MOVED)
            {}
    };


    class MouseScrollEvent : public MouseEventsDetails::MouseStateAction
    {
    public:
        MouseScrollEvent(double xoff, double yoff) :
                MouseStateAction(xoff, yoff, RB_MOUSE_SCROLLED)
            {}
    };
    // -----------------
}
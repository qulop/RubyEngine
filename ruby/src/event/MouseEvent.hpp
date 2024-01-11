#include "RubyEvents.hpp"



namespace Ruby
{
    // RB_MOUSE_PRESS && RB_MOUSE_RELEASED
    class MouseButtonAction : public Event
    {
    public:
        RUBY_NODISCARD int GetButton(void) const
        { 
            RUBY_ASSERT(m_button >= 0);
            return m_button; 
        }

    protected:
        MouseButtonAction(int button, EventType type) :
                Event(type), 
                m_button(button) 
            {}

    private:
        int m_button = -1;    
    };


    class MousePressEvent : public MouseButtonAction
    {
    public:
        MousePressEvent(int button) :
                MouseButtonAction(button, RB_MOUSE_PRESSED) 
            {}
    };


    class MouseReleaseEvent : public MouseButtonAction
    {
    public:
        MouseReleaseEvent(int button) : 
                MouseButtonAction(button, RB_MOUSE_RELEASED)
            {}
    };
    // -----------------

    // RB_MOUSE_MOVED && RB_MOUSE_SCROLLED
    class MouseStateAction : public Event
    {
    public:
        RUBY_NODISCARD double GetX(void) const
        {
            RUBY_ASSERT(m_xoff >= 0);
            return m_xoff;
        }

        RUBY_NODISCARD double GetY(void) const
        {
            RUBY_ASSERT(m_yoff >= 0);
            return m_yoff;
        }

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


    class MouseMoveEvent : public MouseStateAction
    {
    public:
        MouseMoveEvent(double xoff, double yoff) :
                MouseStateAction(xoff, yoff, RB_MOUSE_MOVED)
            {}
    };


    class MouseScrollEvent : public MouseStateAction
    {
    public:
        MouseScrollEvent(double xoff, double yoff) :
                MouseStateAction(xoff, yoff, RB_MOUSE_SCROLLED)
            {}
    };
    // -----------------
}
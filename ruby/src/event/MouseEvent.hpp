#include "EventBase.hpp"


namespace Ruby
{

    class MousePressEvent : public Event
    {
    public:
        MousePressEvent(int button) :
                Event(EventType::MOUSE_BUTTON_PRESSED_EVENT), 
                m_button(button) {}
    
        RUBY_NODISCARD int GetButton(void) const
        { 
            RUBY_ASSERT(m_button >= 0);
            return m_button; 
        }

        bool IsPressed(void) const
        { return m_isPressed; }

    private:
        int m_button = -1;    
        bool m_isPressed = false;
    };


    class MouseMoveEvent : public Event
    {
    public:
        MouseMoveEvent(double xoff, double yoff) :
            Event(EventType::MOUSE_MOVED_EVENT), 
            m_xoff(xoff), 
            m_yoff(yoff) {}

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

    private:
        double m_xoff = -1;
        double m_yoff = -1;
    };


}
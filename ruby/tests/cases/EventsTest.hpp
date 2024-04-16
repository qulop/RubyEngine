#pragma once

#include <event/EventManager.hpp>
#include <utility/Keys.hpp>
#include <window/WindowImpl.hpp>


namespace Ruby::Tests
{
    std::vector<bool> g_results;  // REPLACE

    namespace Details::Events
    {
        void mousePressedFunction(IEvent* event)
        {
            if (auto e = dynamic_cast<MousePressEvent*>(event))
                g_results.push_back(true);
        }

        class TestClass
        {
        public:
            void Callback(IEvent* event)
            {
                if (auto e = dynamic_cast<KeyboardKeyPressed*>(event))
                    g_results.push_back(true);
            }
        };
    }




    class EventsTest
    {
    public:
        RUBY_NODISCARD static bool Test()
        {
            using namespace Details::Events;

            RubyVector<Listener> listeners;

            listeners.emplace_back(addEventListener(RUBY_MOUSE_PRESSED, Details::Events::mousePressedFunction));
            exciteEvent(MousePressEvent{ 0 });

            TestClass testInst;
            listeners.emplace_back(addEventListener(RUBY_KEY_PRESSED, &TestClass::Callback, &testInst));
            exciteEvent(KeyboardKeyPressed{ Keys::KEY_G, GLFW_PRESS });

            listeners.emplace_back(addEventListener(RUBY_KEY_RELEASED, [&](IEvent* event) {
                if (auto e = dynamic_cast<KeyboardKeyReleased*>(event))
                    g_results.push_back(true);
            }));
            exciteEvent(KeyboardKeyReleased{ Keys::KEY_G, GLFW_RELEASE });


            for (auto i : g_results)
                if (!i)
                    return false;


            return std::ranges::all_of(listeners.begin(), listeners.end(),
               [](auto&& listener){
                    if (!removeEventListener(listener))
                        return false;
            });
        }
    };
}

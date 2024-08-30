#pragma once

#include <tests/framework/RubyTestsFramework.hpp>
#include <events/EventManager.hpp>
#include <utility/Keys.hpp>
#include <core/IWindow.hpp>


RUBY_TESTS_SUITE {
    namespace Details::Events {
        std::vector<bool> g_results;  // REPLACE

        void mousePressedFunction(IEvent* event) {
            if (isInstanceOf<MousePressEvent>(event))
                g_results.push_back(true);
        }

        class EventsClassCallbackTest {
        public:
            void Callback(IEvent* event) {
                if (isInstanceOf<KeyboardKeyPressed>(event))
                    g_results.push_back(true);
            }
        };
    }

    RUBY_DEFINE_TEST("EventsTest", Events) {
        using namespace Details::Events;
        
        RubyVector<EventListener> listeners;
        EventsClassCallbackTest testInst;

        listeners.emplace_back(
            addEventListener(RUBY_MOUSE_PRESSED, 
                            Details::Events::mousePressedFunction));

        listeners.emplace_back(
            addEventListener(RUBY_KEY_PRESSED, 
                            &EventsClassCallbackTest::Callback, &testInst));

        listeners.emplace_back(
            addEventListener(RUBY_KEY_RELEASED, 
                            [&](IEvent* event) {
                                if (isInstanceOf<KeyboardKeyReleased>(event))
                                    g_results.push_back(true);
        }));

        exciteEvent(MousePressEvent{ 0 });
        exciteEvent(KeyboardKeyPressed{ Keys::KEY_G, GLFW_PRESS });
        exciteEvent(KeyboardKeyReleased{ Keys::KEY_G, GLFW_RELEASE });

        for (auto i : g_results)
            RUBY_TESTS_ASSERT_TRUE(i);

        for (auto lst : listeners)
            RUBY_TESTS_ASSERT_TRUE(removeEventListener(lst));
    }
}

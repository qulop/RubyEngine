#pragma once

#include "Core.hpp"
#include "Logger.hpp"
#include <event/EventManager.hpp>
#include <event/Event.hpp>
#include <functional>
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <glfw/include/GLFW/glfw3.h>


namespace Ruby
{
    void RUBY_API getScreenResolution(int& w, int& h);


    struct RUBY_API WindowAttributes
    {
        std::string title = "My Visual Novel";
        int width = -1;
        int height = -1;
        GLFWmonitor* monitor = nullptr;

        WindowAttributes(void) = default;

        WindowAttributes(const std::string& t, int w, int h, GLFWmonitor* m) :
            title(t), width(w), height(h), monitor(m) {}
    };


    class Window
    {
    public:
        Window(WindowAttributes& wa);

        void Update(void);

        void OnEvent(MouseMoveEvent& event);

        ~Window(void);

    private:
        void Init(WindowAttributes& wa);

    private:
        GLFWwindow* m_window;
    };
}
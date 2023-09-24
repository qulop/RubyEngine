#pragma once

#include "Core.hpp"
#include "Logger.hpp"
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <glfw/include/GLFW/glfw3.h>


namespace Ruby
{
    void RUBY_API getScreenResolution(int& w, int& h);

    void setGlfwErrCallback(int err, const char* desc);


    struct RUBY_API WindowAttributes
    {
        std::string title = "RVN-Project";
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
        Window(void);

        Window(WindowAttributes& wa);

        void ShowWindow(void);

        Window& operator=(WindowAttributes& wa);

        Window(const Window&) = delete;

        ~Window(void);

    private:
        void Init(WindowAttributes& wa);

    private:
        GLFWwindow* m_window;
    };
}
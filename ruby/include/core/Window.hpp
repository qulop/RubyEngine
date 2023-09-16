#pragma once

#include "Core.hpp"
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <glfw/include/GLFW/glfw3.h>


namespace Ruby
{
    void RUBY_API getScreenResolution(int& w, int& h);

    void setGlfwErrCallback(int err, const char* desc);


    struct RUBY_API WindowAttrubutes
    {
        const char* title = "RVN-Project";
        int width = -1;
        int height = -1;
        GLFWmonitor* monitor = nullptr;

        WindowAttrubutes(void) = default;

        WindowAttrubutes(const char*& t, int w, int h, GLFWmonitor* m) :
            title(t), width(w), height(h), monitor(m) {}
    };


    class Window
    {
    public:
        Window(void);

        Window(WindowAttrubutes& wa);

        void showWindow(void);

        Window& operator=(WindowAttrubutes& wa);

        ~Window(void);

    private:
        void init(WindowAttrubutes& wa);

    private:
        GLFWwindow* m_window;
    };
}
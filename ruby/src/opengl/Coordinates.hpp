#pragma once

#include <core/WindowProps.hpp>
#include <iostream>
#include <array>


// { 340, 1234,   }
namespace Ruby
{
    template<int N>
    std::array<GLfloat, N> toNDC(const std::array<int, N>& wc, SizeStruct windowScale, bool isAddZ=true)
    {
        // std::array<GLfloat, N> out;
        // out.fill(0);

        // for (auto i = 0; i < N; i++)
        // {
        //     if (i % 2 == 0) // for X axis
        //     {

        //     }
        //     else if (i % 3 == 0)    // Z


        //     out.at(i) = ndc;
        // }

        // return out;
    }


    inline GLuint buildOpenglShader(GLenum type, const GLchar* shaderSrc)
    {
        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &shaderSrc, nullptr);
        glCompileShader(shader);

        GLint ok;
        GLchar buffer[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
        if (!ok)
        {
            glGetShaderInfoLog(shader, sizeof(buffer), nullptr, buffer);
            std::cout << "<!!!> OpenGL shader compilation failed <!!!>\n";
            std::cout << "Type: " << type << std::endl;
            std::cout << "Sources: " << shaderSrc << std::endl;
            std::cout << "Message: " << buffer << std::endl;
        }

        return shader;
    }
}
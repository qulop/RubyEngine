#pragma once

#include <glad/glad.h>
#include <glm/matrix.hpp>

#include <utility/Definitions.hpp>

#include <vector>


namespace Ruby
{
    template<typename... Args>
    concept UniformAllowedType = (std::is_integral_v<Args...> || std::is_floating_point_v<Args...>);


    // You must specify minimum one necessarily argument(i.e. head), and up to three optional(args).
    template<UniformAllowedType Head, UniformAllowedType... Args>
    void uniform(GLuint loc, Head&& head, Args&&... args)
    {
        constexpr bool isInt = std::is_same_v<Head, int>;
        constexpr bool isFloat = std::is_same_v<Head, float>;

        // The total amount is calculated here
        // Here <1> is head
        switch (sizeof...(args) + 1)
        {
            case 1:
            {
                if constexpr (isInt)
                    glUniform1i(loc, head);
                else if constexpr (isFloat)
                    glUniform1f(loc, head);
                else 
                    glUniform1d(loc, head);
                break;
            }
            case 2:
            {
                if constexpr (isInt)
                    glUniform2i(loc, head, args...);
                else if constexpr (isFloat)
                    glUniform2f(loc, head, args...);
                else 
                    glUniform2d(loc, head, args...);
                break;
            }
            case 3:
            {
                if constexpr (isInt)
                    glUniform3i(loc, head, args...);
                else if constexpr (isFloat)
                    glUniform3f(loc, head, args...);
                else 
                    glUniform3d(loc, head, args...);
            }
            case 4:
            {
                if constexpr (isInt)
                    glUniform4i(loc, head, args...);
                else if constexpr (isFloat)
                    glUniform4f(loc, head, args...);
                else 
                    glUniform4d(loc, head, args...);
                break;
            }
        } 
    }


    /*
        Tx - type of array;
        N - array dimension(that is, what is substituted for '*' in glUniform*v).

        Assignment of other parameters see on https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUniform.xhtml
    */
    template<UniformAllowedType Tx, size_t N>
    void uniform(GLuint loc, size_t count, const std::vector<Tx>& arr)
    {
        RUBY_STATIC_ASSERT(N >= 1 && N <= 4, "Uniform can only receive maximum 4 dimensional array(and 1 minimum).");

        constexpr bool isInt = std::is_same_v<Tx, int>;
        constexpr bool isFloat = std::is_same_v<Tx, float>;
        constexpr Tx* const rawArray = arr.data();

        switch (N)
        {
            case 1:
            {
                if constexpr (isInt)
                    glUniform1iv(loc, count, rawArray);
                else if constexpr (isFloat)
                    glUniform1fv(loc, count, rawArray);
                else 
                    glUniform1dv(loc, count, rawArray);
                break;
            }
            case 2:
            {
                if constexpr (isInt)
                    glUniform2iv(loc, count, rawArray);
                else if constexpr (isFloat)
                    glUniform2fv(loc, count, rawArray);
                else 
                    glUniform2dv(loc, count, rawArray);
                break;
            }
            case 3:
            {
                if constexpr (isInt)
                    glUniform3iv(loc, count, rawArray);
                else if constexpr (isFloat)
                    glUniform3fv(loc, count, rawArray);
                else 
                    glUniform3dv(loc, count, rawArray);
                break;
            }
            case 4:
            {
                if constexpr (isInt)
                    glUniform4iv(loc, count, rawArray);
                else if constexpr (isFloat)
                    glUniform4fv(loc, count, rawArray);
                else 
                    glUniform4dv(loc, count, rawArray);
                break;
            }

        }
    }
}


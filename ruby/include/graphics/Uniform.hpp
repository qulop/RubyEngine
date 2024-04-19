#pragma once

#include <glad/glad.h>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <utility/Definitions.hpp>

#include <vector>


namespace Ruby
{
    namespace Details::Uniform
    {
        // For glUniform* (not vectorized)
        template<typename Head, typename... Args>
        void uniformNumSeq(GLuint loc, Head&& head, Args&&... args)
        {
            constexpr bool isInt = std::is_integral_v<std::decay_t<Head>>;
            constexpr bool isFloat = std::is_same_v<std::decay_t<Head>, float>;

            constexpr size_t totalArgs = sizeof...(args) + 1;
            if constexpr (totalArgs == 1)
            {
                if constexpr (isInt)
                    glUniform1i(loc, head);
                else if constexpr (isFloat)
                    glUniform1f(loc, head);
                else 
                    glUniform1d(loc, head);
            }
            else if constexpr (totalArgs == 2)
            {
                if constexpr (isInt)
                    glUniform2i(loc, head, args...);
                else if constexpr (isFloat)
                    glUniform2f(loc, head, args...);
                else 
                    glUniform2d(loc, head, args...);
            }
            else if constexpr (totalArgs == 3)
            {
                if constexpr (isInt)
                    glUniform3i(loc, head, args...);
                else if constexpr (isFloat)
                    glUniform3f(loc, head, args...);
                else 
                    glUniform3d(loc, head, args...);
            }
            else if constexpr (totalArgs == 4)
            {
                if constexpr (isInt)
                    glUniform4i(loc, head, args...);
                else if constexpr (isFloat)
                    glUniform4f(loc, head, args...);
                else 
                    glUniform4d(loc, head, args...);
            }
        }


        template<typename Tx, size_t N>
        void uniformVec(GLuint loc, GLsizei count, const Tx* ptr)
        {
            constexpr bool isInt = std::is_integral_v<std::decay_t<Tx>>;
            constexpr bool isFloat = std::is_same_v<std::decay_t<Tx>, float>;

            if constexpr (N == 1)
            {
                if constexpr (isInt)
                    glUniform1iv(loc, count, ptr);
                else if constexpr (isFloat)
                    glUniform1fv(loc, count, ptr);
                else 
                    glUniform1dv(loc, count, ptr);
            }
            if constexpr (N == 2)
            {
                if constexpr (isInt)
                    glUniform2iv(loc, count, ptr);
                else if constexpr (isFloat)
                    glUniform2fv(loc, count, ptr);
                else 
                    glUniform2dv(loc, count, ptr);
            }
            if constexpr (N == 3)
            {
                if constexpr (isInt)
                    glUniform3iv(loc, count, ptr);
                else if constexpr (isFloat)
                    glUniform3fv(loc, count, ptr);
                else 
                    glUniform3dv(loc, count, ptr);
            }
            if constexpr (N == 4)
            {
                if constexpr (isInt)
                    glUniform4iv(loc, count, ptr);
                else if constexpr (isFloat)
                    glUniform4fv(loc, count, ptr);
                else 
                    glUniform4dv(loc, count, ptr);
            }
        }


        template<size_t Cols, size_t Rows>
        void uniformMatrix(GLuint loc, GLsizei count, bool isTransposed, const float* ptr)
        {
            if constexpr (Cols == 2)
            {
                if constexpr (Rows == Cols)
                    glUniformMatrix2fv(loc, count, isTransposed, ptr);
                else if constexpr (Rows == 3)
                    glUniformMatrix2x3fv(loc, count, isTransposed, ptr);
                else if constexpr (Rows == 4)
                    glUniformMatrix2x4fv(loc, count, isTransposed, ptr);
            }
            else if constexpr (Cols == 3)
            {
                if constexpr (Rows == 2)
                    glUniformMatrix3x2fv(loc, count, isTransposed, ptr);
                else if constexpr (Rows == Cols)
                    glUniformMatrix3fv(loc, count, isTransposed, ptr);
                else if constexpr (Rows == 4)
                    glUniformMatrix3x4fv(loc, count, isTransposed, ptr);
            }
            else
            {
                if constexpr (Rows == 2)
                    glUniformMatrix4x2fv(loc, count, isTransposed, ptr);
                else if constexpr (Rows == 3)
                    glUniformMatrix4x3fv(loc, count, isTransposed, ptr);
                else if constexpr (Rows == Cols)
                    glUniformMatrix4fv(loc, count, isTransposed, ptr);
            }
        }
    }

    template<typename... Args>
    concept UniformAllowedType = (std::is_integral_v<typename std::decay<Args...>::type>) ||
                                (std::is_floating_point_v<typename std::decay<Args...>::type>);


    // You must specify minimum one necessarily argument(i.e. head), and up to three optional(args).
    template<UniformAllowedType Head, UniformAllowedType... Args>
    void uniform(GLuint loc, Head&& head, Args&&... args)
    {
        static_assert(sizeof...(args) <= 3, "Uniform cannot take more than 4 arguments");

        Details::Uniform::uniformNumSeq(loc, head, args...);
    }

    /*
        Tx - type of array;
        N - array dimension(that is, what is substituted for '*' in glUniform*v).

        Assignment of other parameters see on https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUniform.xhtml
    */
    template<UniformAllowedType Tx, size_t N>
        requires (N >= 1 && N <= 4)
    void uniform(GLuint loc, GLsizei count, const std::vector<Tx>& arr)
    {
        Details::Uniform::uniformVec<Tx, N>(loc, count, arr.data());
    }


    template<size_t Cols, size_t Rows=Cols, typename MatrixType>
        requires (Rows <= 4) && (Cols <= 4)
    void uniform(GLuint loc, GLsizei count, bool isTransposed, const MatrixType& matrix)
    {
        const auto ptr = static_cast<const float*>(glm::value_ptr(matrix));

        Details::Uniform::uniformMatrix<Cols, Rows>(loc, count, isTransposed, ptr);
    }
}


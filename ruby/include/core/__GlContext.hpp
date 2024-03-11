/********
    Will delete, after render is be ready
*********/

#pragma once

#include <glad/glad.h>
#include <glm/vec4.hpp>

#include <render/shaders/ShaderProgram.hpp>
#include <render/texture/Texture2D.hpp>

#include <functional>


namespace Ruby
{
    class __GlContext
    {
    public:
        __GlContext(const GLfloat buffer[], size_t size, const ShaderProgram& program, const GLuint ind[], size_t isize)
        {
            glGenBuffers(1, &vbo);
            glGenVertexArrays(1, &vao);
            glGenBuffers(1, &ibo);

            glBindVertexArray(vao);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, isize, ind, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
            glEnableVertexAttribArray(1);

            glVertexAttribPointer(2, 2, GL_UNSIGNED_INT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
            glEnableVertexAttribArray(2);

            glBindVertexArray(0);
        }


        void AddTexture(Texture2D texture)
        {
            this->texture = texture;
        }


        void Update(const glm::vec4& cc, std::function<void(void)>&& pred)
        {
            glClearColor(cc.r, cc.g, cc.b, cc.a);
            glClear(GL_COLOR_BUFFER_BIT);

            texture.Use();
            pred();

            glBindVertexArray(vao);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }


        ~__GlContext()
        {
            glDeleteBuffers(1, &vbo);
            glDeleteBuffers(1, &ibo);
            glDeleteVertexArrays(1, &vao);
        }


    private:
        GLuint vbo;
        GLuint vao;
        GLuint ibo;

        Texture2D texture;
    };
}
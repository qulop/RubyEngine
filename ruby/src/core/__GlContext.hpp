/********
    Will delete, after render is be ready
*********/

#pragma once

#include <glad/glad.h>
#include <glm/vec4.hpp>

#include <render/ShaderProgram.hpp>
#include <graphics/Texture2D.hpp>
#include <graphics/Color.hpp>
#include <render/VertexArray.hpp>
#include <render/Buffers.hpp>

#include <functional>


namespace Ruby
{
    class __GlContext
    {
    public:
        __GlContext() = default;

        __GlContext(GLfloat buffer[], size_t size, const ShaderProgram& program, GLuint ind[], size_t isize)
        { Add(buffer, size, program, ind, isize); }

        void Add(GLfloat buffer[], size_t size, const ShaderProgram& program, GLuint ind[], size_t isize)
        {
            m_program = program;
            vbo = VertexBuffer::Create(buffer, size);
            vao = VertexArray::Create();
            ibo = IndexBuffer::Create(ind, isize);

            vbo->SetLayoutTypes({ ShaderDataTypes::VEC3, ShaderDataTypes::VEC3, ShaderDataTypes::VEC2 });
            vao->SetVBO(vbo);

            vao->Unbind();

//            glGenBuffers(1, &vbo);
//            glGenVertexArrays(1, &vao);
//            glGenBuffers(1, &ibo);
//
//            glBindVertexArray(vao);
//
//            glBindBuffer(GL_ARRAY_BUFFER, vbo);
//            glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);
//
//            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
//            glBufferData(GL_ELEMENT_ARRAY_BUFFER, isize, ind, GL_STATIC_DRAW);

//            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
//            glEnableVertexAttribArray(0);
//
//            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//            glEnableVertexAttribArray(1);
//
//            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
//            glEnableVertexAttribArray(2);
//
//            glBindVertexArray(0);
        }

        void AddTexture(Texture2D texture)
        {
            this->m_texture = texture;
        }


        void Update(const Color& color)
        {
            glClearColor(color.Red(), color.Green(), color.Blue(), color.Alpha());
            glClear(GL_COLOR_BUFFER_BIT);

            m_program.UseProgram();
            vao->Bind();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            vao->Unbind();
        }


    private:
        Ptr<VertexBuffer> vbo;
        Ptr<VertexArray> vao;
        Ptr<IndexBuffer> ibo;

        ShaderProgram m_program;
        Texture2D m_texture;
    };
}
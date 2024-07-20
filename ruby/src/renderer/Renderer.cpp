#include "Renderer.hpp"

#include <utility/Definitions.hpp>
#include <utility/StdInc.hpp>
#include <glad/glad.h>


namespace Ruby {
    static bool s_isRendererAPIInitialized = false;

    template<typename Func, typename... Args>
    void dropIfRendererAPINotInitialized(Func&& func, Args&&... args) {
        if (!s_isRendererAPIInitialized)
            RUBY_WRECK("dropIfRendererAPINotInitialized() : Renderer API was not initialized!");

        std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
    }


    void initRendererAPI() {
        // Here will be something... I hope
        // I just don't know what to write here now
        // I write this function just because referenced code has this function, looool

        s_isRendererAPIInitialized = true;
    }

    void setViewport(u32 x, u32 y, u32 width, u32 height) {
        dropIfRendererAPINotInitialized(glViewport, x, y, width, height);
    }

    void clearBuffers() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void clearColor(const Color& color) {
        dropIfRendererAPINotInitialized(glClearColor, color.Red(), color.Green(), color.Blue(), color.Alpha());
    }

    void clearColor(f32 r, f32 g, f32 b, f32 a) {
        dropIfRendererAPINotInitialized(glClearColor, r, g, b, a);
    }

    void drawIndexed(const VertexArray& vao, u32 indexCount) {
        if (!indexCount)
            indexCount = vao.GetEBO().GetCount();

        vao.Bind();
        dropIfRendererAPINotInitialized(glDrawElements, GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
    }

    void drawLines(const VertexArray& vao, u32 vetexCount){
        vao.Bind();
        dropIfRendererAPINotInitialized(glDrawArrays, GL_LINE, 0, vetexCount);
    }

    void setLineWidth(f32 width) {
        dropIfRendererAPINotInitialized(glLineWidth, width);
    }



    void Renderer::Init() {
        initRendererAPI();


    }


    void Renderer::Shutdown()
    { RUBY_NOT_IMPLEMENTED; }


    void Renderer::DrawRotatedObject()
    { RUBY_NOT_IMPLEMENTED; }


    void Renderer::DrawQuad()
    { RUBY_NOT_IMPLEMENTED; }


    void Renderer::DrawLine()
    { RUBY_NOT_IMPLEMENTED; }


    void Renderer::DrawCircle()
    { RUBY_NOT_IMPLEMENTED; }


    void Renderer::DrawChar()
    { RUBY_NOT_IMPLEMENTED; }


    void Renderer::DrawString()
    { RUBY_NOT_IMPLEMENTED; }
}
#pragma once

#include <graphics/Color.hpp>
#include "VertexArray.hpp"
#include "Buffers.hpp"


namespace Ruby {
    void initRendererAPI();

    void setViewport(u32 x, u32 y, u32 width, u32 height);

    void clearBuffers();
    void clearColor(const Color& color);
    void clearColor(f32 r, f32 g, f32 b, f32 a);

    void drawIndexed(const VertexArray& vao, u32 indexCount);
    void drawLines(const VertexArray& vao, u32 vetexCount);
    void setLineWidth(f32 width);


    class Renderer {
    public:
        static void Init();
        static void Shutdown();

        static void DrawRotatedObject();

        static void DrawQuad();

        static void DrawLine();

        static void DrawCircle();

        static void DrawChar();
        static void DrawString();
    };
}
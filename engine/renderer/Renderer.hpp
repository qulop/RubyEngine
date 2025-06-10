#pragma once

#include <graphics/Color.hpp>
#include <math/Vec.hpp>

#include "VertexArray.hpp"
#include "Buffers.hpp"


namespace Ruby {
    class RUBY_API Renderer {
    public:
        static void Init(u32 vpWidth, u32 vpHeight);
        static void Shutdown();

        static void DrawRotatedObject();

        static void DrawQuad();


        static void DrawLine(const Math::Vec3& start, const Math::Vec3& end, const Color& color);

        static void DrawCircle();

        static void DrawChar();
        static void DrawString();
    };
}
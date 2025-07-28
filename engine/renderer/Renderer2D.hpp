#pragma once

#include <graphics/Color.hpp>
#include <types/Singleton.hpp>

#include "VertexArray.hpp"
#include "Shader.hpp"

#include <glm/matrix.hpp>


namespace Ruby {
    struct RenderStats2D {
        size_t drawCalls = 0;
        size_t trianglesTotalCount = 0;
    };


    class RUBY_API Renderer2D : public Singleton<Renderer2D> {
        RUBY_DEFINE_SINGLETON(Renderer2D);

    public:
        static void Init(u32 vpWidht, u32 vpHeight);

    public:
        void Shutdown();

        void DrawQuad(const glm::mat3& coords, const Color& color);

    private:
        void InitFromInstance(u32 vpWidth, u32 vpHeight);
        
        void InitializeForQuad();
    
    private:
        IndexBuffer* m_quadIndexBuffer = nullptr;
        VertexBuffer* m_quadVertexBuffer = nullptr;
        VertexArray* m_quadVertexArray = nullptr;
        Shader* m_quadShader = nullptr;

        RenderStats2D m_stats;
    };
}
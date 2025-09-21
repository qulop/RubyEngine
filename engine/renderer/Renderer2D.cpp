#include "Renderer2D.hpp"

#include <utility/Definitions.hpp>
#include <utility/Assert.hpp>
#include <utility/Panic.hpp>
#include <types/Logger.hpp>
#include <types/StdInc.hpp>
#include <glad/glad.h>

#include <renderer/shaders/Shader.hpp>

#include "RendererAPI.hpp"



namespace Ruby {
    void Renderer2D::Init(u32 vpWidht, u32 vpHeight) {
        GetInstance().InitFromInstance(vpWidht, vpHeight);
    }


    void Renderer2D::InitFromInstance(u32 vpWidth, u32 vpHeight) {
        RUBY_DEBUG("Renderer initialization started...");

        RendererAPI::Init(vpWidth, vpHeight);

        RUBY_INFO("GPU Vendor: {}\nGPU Renderer: {}", 
                   RendererAPI::GetVendor(), 
                   RendererAPI::GetRendererName()
        );
        RUBY_INFO("Maximum vertex attributes: {}", RendererAPI::GetMaxVertexAttribs());
    }


    void Renderer2D::Shutdown() {
        RUBY_NOT_IMPLEMENTED();
    }

    void Renderer2D::DrawQuad(const glm::mat3& coords, const Color& color) {
    
    
    }


    void Renderer2D::InitializeForQuad() {
        
    }
}
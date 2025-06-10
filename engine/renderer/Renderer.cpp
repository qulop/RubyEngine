#include "Renderer.hpp"

#include <utility/Definitions.hpp>
#include <utility/Assert.hpp>
#include <utility/Panic.hpp>
#include <types/Logger.hpp>
#include <types/StdInc.hpp>
#include <glad/glad.h>

#include "RendererAPI.hpp"



namespace Ruby {
    namespace Details::Renderer {
        static void printDebugInfo() {
            RUBY_DEBUG("GPU: {}, Renderer: {}", RendererAPI::GetVendor(), RendererAPI::GetRendererName());
            RUBY_DEBUG("Used graphic API: {}, Version: {}",
                       enumValueToString(RendererAPI::GetUsedAPI()).value_or(""),
                       RendererAPI::GetVersionOfAPI());
            RUBY_DEBUG("Shading language version: {}", RendererAPI::GetShadingLanguageVersion());
        }
    }



    void Renderer::Init(u32 vpWidth, u32 vpHeight) {
        Details::Renderer::printDebugInfo();

        RendererAPI::Init(vpWidth, vpHeight);
    }


    void Renderer::Shutdown() {
        RUBY_NOT_IMPLEMENTED();
    }

    void Renderer::DrawRotatedObject() { 
        RUBY_NOT_IMPLEMENTED(); 
    }


    void Renderer::DrawQuad() { 
        RUBY_NOT_IMPLEMENTED(); 
    }


    void Renderer::DrawLine(const Math::Vec3& start, const Math::Vec3& end, const Color& color) {
        
    }


    void Renderer::DrawCircle() { 
        RUBY_NOT_IMPLEMENTED(); 
    }


    void Renderer::DrawChar() { 
        RUBY_NOT_IMPLEMENTED(); 
    }


    void Renderer::DrawString() { 
        RUBY_NOT_IMPLEMENTED(); 
    }
}
#include "RenderPipelineGL.hpp"

#include <glad/glad.h>


namespace Kiwi::OpenGL {
    void RenderPipelineGL::SetViewport(const IRect& viewport) {
        Super::SetViewport(viewport);

        glViewport(viewport.MinimumCoordinate().x, viewport.MinimumCoordinate().y, viewport.Width(), viewport.Height());
    }

    bool RenderPipelineGL::Init() {
        if (!Super::Init()) {
            return false;
        }


    }

    String RenderPipelineGL::GetRendererDeviceVendor() const {
        return String{ (const char*)glGetString(GL_VENDOR) };
    }

    String RenderPipelineGL::GetRendererDeviceName() const {
        return String{ (const char*)glGetString(GL_RENDERER) };
    }

    void RenderPipelineGL::ClearBuffers(EClearBuffers buffersToClear) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    void RenderPipelineGL::ClearColor(const Color& color) {
        glClearColor(color.Red(), color.Green(), color.Blue(), color.Alpha());
    }

    void RenderPipelineGL::ClearColor(const Vec4 &color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void RenderPipelineGL::ClearColor(f32 r, f32 g, f32 b, f32 a) {
        glClearColor(r, g, b, a);
    }
}

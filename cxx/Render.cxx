#ifdef RUBY_MSVC_USED
    #pragma warning(push)
    #pragma warning(disable : 4715)
#endif

#include "../ruby/src/render/Buffers.cpp"
#include "../ruby/src/render/VertexArray.cpp"
#include "../ruby/src/render/ShaderDataTypes.cpp"
#include "../ruby/src/render/Shader.cpp"

// Implementation for specific graphic API:
#include "../ruby/src/render/gl/GlBuffers.cpp"
#include "../ruby/src/render/gl/GlVertexArray.cpp"
#include "../ruby/src/render/gl/GlShader.cpp"

#ifdef RUBY_MSVC_USED
    #pragma warning(pop)
#endif
#include <render/Shader.hpp>
#include <render/gl/GlShader.hpp>


namespace Ruby
{
    Ptr<Shader> Shader::Create()
    {
        return std::make_shared<GlShader>();
    }

    Ptr<Shader> Shader::Create(const RubyString& vertexSrc, const RubyString& fragmentSrc)
    {
        return std::make_shared<GlShader>(vertexSrc, fragmentSrc);
    }
}
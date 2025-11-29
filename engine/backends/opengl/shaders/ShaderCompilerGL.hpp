#pragma once

#include <renderer/shaders/ShaderCompiler.hpp>
#include <renderer/shaders/PreprocessorGLSL.hpp>

#include <backends/opengl/basic/TypesGL.hpp>



namespace Ruby::OpenGL {
    class ShaderCompilerGL : public Ruby::AShaderCompiler {
        using SourcesMap = typename PreprocessorGLSL::SourcesMap;
    public:
        RUBY_NODISCARD UniquePtr<AShader> CompileFile(const File& sourceFile) override;

        RUBY_NODISCARD static bool CheckCompilationOrLinkingResult(GLuint target, EShaderStage type);

    private:
        RUBY_NODISCARD GlID CompileShaderStage(EShaderStage stage, StringView src) const;

        RUBY_NODISCARD GlID CreateFromSpirVByteCode(EShaderStage stage, StringView entryPoint, const Vector<u32>& byteCode) const;
    };
}
#include "Shader.hpp"

#include "PreprocessorGLSL.hpp"

#include <utility/Algorithm.hpp>
#include <types/Logger.hpp>


namespace Ruby {
    Opt<Shader::UncompiledSourcesMap> Shader::PreprocessSource(const String& src) const {
        // TODO: Add error handling - either inside in TryPreprocess() or here
        return PreprocessorGLSL::TryPreprocess(src).value_or(nullopt);
    }
}
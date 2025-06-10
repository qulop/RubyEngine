#include "Shader.hpp"
#include "Shader.hpp"

#include <utility/Algorithm.hpp>
#include <utility/Assert.hpp>
#include <utility/Cast.hpp>
#include <types/Logger.hpp>
#include <types/File.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>


namespace Ruby {
    static void getShaderProcessError(GLuint target, ShaderTypes type = ShaderTypes::RUBY_SHADER_PROGRAM) {
        GLint hasNoErrors = 0;
        bool isProgramReceived = (type == ShaderTypes::RUBY_SHADER_PROGRAM); // Shader program received

        if (isProgramReceived)
            glGetProgramiv(target, GL_LINK_STATUS, &hasNoErrors);
        else
            glGetShaderiv(target, GL_COMPILE_STATUS, &hasNoErrors);

        if (hasNoErrors)
            return;

        GLchar buffer[256];
        auto bufferSize = static_cast<GLsizei>(std::size(buffer));
        if (isProgramReceived)
            glGetProgramInfoLog(target, bufferSize, nullptr, buffer);
        else
            glGetShaderInfoLog(target, bufferSize, nullptr, buffer);

        auto typeName = enumValueToString(type).value_or("");
        auto linkingOrCompiling = (isProgramReceived) ? "linking" : "compiling";

        RUBY_ERROR("{}: an error occurred while {} shader. {}", typeName, linkingOrCompiling, buffer);
    }


    template<size_t N, typename Type>
        requires (N >= 1 && N <= 4) && (std::is_floating_point_v<Type> || std::is_integral_v<Type>)
    void setUniform(u32 loc, const glm::vec<N, Type, glm::defaultp>& vec) {
        #ifdef RUBY_MSVC_USED
            #pragma warning(push)
            #pragma warning(disable : 4244)
        #endif

        constexpr bool isInt = std::is_integral_v<Type>;
        if constexpr (isInt) {
            if constexpr (N == 1)
                glUniform1i(loc, vec.x);
            else if constexpr (N == 2)
                glUniform2i(loc, vec.x, vec.y);
            else if constexpr (N == 3)
                glUniform3i(loc, vec.x, vec.y, vec.z);
            else
                glUniform4i(loc, vec.x, vec.y, vec.z, vec.w);
            return;
        }

        if constexpr (N == 1)
            glUniform1f(loc, vec.x);
        else if constexpr (N == 2)
            glUniform2f(loc, vec.x, vec.y);
        else if constexpr (N == 3)
            glUniform3f(loc, vec.x, vec.y, vec.z);
        else
            glUniform4f(loc, vec.x, vec.y, vec.z, vec.w);

        #ifdef RUBY_MSVC_USED
            #pragma warning(pop)
        #endif
    }


//    Shader::Shader(const String& unifiedShadersPath) {
//        auto src = File::ReadStatic(unifiedShadersPath).value_or("");
//        if (src.empty()) {
//            RUBY_ERROR("Shader::SplitUnifiedShaderFile() : Failed to split file {}", unifiedShadersPath);
//            return;
//        }
//
//        m_sources[RUBY_VERTEX_SHADER] = SplitVertexShader(src);
//    }

    Shader::Shader(const String& vertexPath, const String& fragmentPath) {
        m_sources[RUBY_VERTEX_SHADER] = std::move(File::ReadStatic(vertexPath).value_or(""));
        m_sources[RUBY_FRAGMENT_SHADER] = std::move(File::ReadStatic(fragmentPath).value_or(""));
    }

    std::string_view Shader::GetSource(ShaderTypes type) const {
        return m_sources.at(type);
    }

    u32 Shader::GetShaderID(ShaderTypes type) const {
        return m_shadersId.at(type);
    }

    u32 Shader::GetProgramID() const {
        return m_programId;
    }

    u32 Shader::GetUniformLocation(const char* name) const {
        return glGetUniformLocation(m_programId, name);
    }

    void Shader::Bind() const {
        glUseProgram(m_programId);
    }

    void Shader::Unbind() const {
        glUseProgram(0);
    }

    void Shader::AddSource(ShaderTypes type, const String& src) {
        m_sources[type] = src;
    }

    void Shader::AddFile(ShaderTypes type, const String& path) {
        m_sources[type] = std::move(File::ReadStatic(path).value_or(""));
    }

    bool Shader::IsEmpty() const {
        return m_sources.empty();
    }

    bool Shader::IsReady() const {
        return m_isReady;
    }

    void Shader::Compile() {
        for (const auto& [type, source]: m_sources)
            m_shadersId[type] = CompileShader(type, source.data());

        m_programId = glCreateProgram();
        for (const auto& id : m_shadersId)
            glAttachShader(m_programId, id.second);
        glLinkProgram(m_programId);

        getShaderProcessError(m_programId);

        RUBY_SWITCH_BOOL(m_isReady);
    }

    void Shader::SetFloat(const char* uniName, f32 value) const {
        setUniform<1, f32>(GetUniformLocation(uniName), glm::vec1{ value });
    }

    void Shader::SetFloat2(const char* uniName, const glm::vec2& vec) const {
        setUniform<2, f32>(GetUniformLocation(uniName), vec);
    }

    void Shader::SetFloat3(const char* uniName, const glm::vec3& vec) const {
        setUniform<3, f32>(GetUniformLocation(uniName), vec);
    }

    void Shader::SetFloat4(const char* uniName, const glm::vec4& vec) const {
        setUniform<4, f32>(GetUniformLocation(uniName), vec);
    }

    void Shader::SetFloatVector(const char* uniName, const f32* data, i32 count) const {
        glUniform1fv((GLint)GetUniformLocation(uniName), count, data);
    }

    void Shader::SetInt(const char* uniName, i32 value) const {
        glm::ivec1 tmp{ value };
        setUniform<1, i32>(GetUniformLocation(uniName), tmp);
    }

    void Shader::SetInt2(const char* uniName, const glm::ivec2& vec) const {
        setUniform<2, i32>(GetUniformLocation(uniName), vec);
    }

    void Shader::SetInt3(const char* uniName, const glm::ivec3& vec) const {
        setUniform<3, i32>(GetUniformLocation(uniName), vec);
    }

    void Shader::SetInt4(const char* uniName, const glm::ivec4& vec) const {
        setUniform<4, i32>(GetUniformLocation(uniName), vec);
    }

    void Shader::SetIntVector(const char* uniName, const i32* data, i32 count) const {
        glUniform1iv((GLint)GetUniformLocation(uniName), count, data);
    }

    void Shader::SetMat2(const char* uniName, const glm::mat2& mat) const {
        glUniformMatrix2fv((GLint)GetUniformLocation(uniName), 1, GL_FALSE, glm::value_ptr(mat));
	}
    
    void Shader::SetMat3(const char* uniName, const glm::mat3& mat) const {
		glUniformMatrix3fv((GLint)GetUniformLocation(uniName), 1, GL_FALSE, glm::value_ptr(mat));
	}

    void Shader::SetMat4(const char* uniName, const glm::mat4& mat) const {
        glUniformMatrix4fv((GLint)GetUniformLocation(uniName), 1, GL_FALSE, glm::value_ptr(mat));
    }

    Shader::~Shader() {
        for (auto i : m_shadersId) {
            glDeleteShader(i.second);
        }
        glDeleteProgram(m_programId);
    }

    u32 Shader::CompileShader(ShaderTypes type, const char* source) const {  // NOLINT
        RUBY_ASSERT(type != ShaderTypes::RUBY_SHADER_PROGRAM, 
            "Shader::CompileShader() : this method can't compile shader program (RUBY_SHADER_PROGRAM received)");
        
        u32 id = glCreateShader(type);
        glShaderSource(id, 1, &source, nullptr);
        glCompileShader(id);

        getShaderProcessError(id, type);

        return id;
    }

//    String Shader::SplitVertexShader(std::string_view src) const {
//        RUBY_ASSERT_BASIC(!src.empty());
//
//        size_t begin = findSubString(src, "#type vertex");
//        size_t end = findSubString(src, "#type fragment");
//        if (end == RUBY_BAD_INDEX)
//            end = src.size() - 1;
//
//        auto res = createStringSlice(src, begin, end);
//    }
//
//
//    std::pair<String, String> Shader::SplitUnifiedShaderFile(const String& path) const {
//        auto fileContent = File::ReadStatic(path).value_or("");
//        if (fileContent.empty()) {
//            RUBY_ERROR("Shader::SplitUnifiedShaderFile() : Failed to split file {}", path);
//        }
//
//        size_t firstDirPos = findSubString(fileContent, "#type");
//        size_t secondDirPos = findSubString(fileContent, "#type", firstDirPos + 6);
//
//        // #type vertex
//        // #type fragment
//    }

}
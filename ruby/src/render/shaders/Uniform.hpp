#pragma once

#include <glad/glad.h>
#include <glm/matrix.hpp>

#include <utility/Definitions.hpp>

#include <typeindex>


namespace Ruby
{
    namespace UfDetails
    {
        // const RubyHashMap<std::type_index, RubyHashMap<size_t, std::function<void(GLuint, ...)>>>
            // functionTable =
        // {
            // { typeid(float), {
                    // 1, glUniform1f }
        // };



        template<typename... Args>
        concept UniformAllowedType = (std::is_integral_v<Args...> || std::is_floating_point_v<Args...>);

        
        // structs
        template<typename Tx>
        struct IsFloat { static constexpr bool value = false; };

        template<>
        struct IsFloat<float> { static constexpr bool value = true; };


        template<typename Tx>
        struct IsDouble { static constexpr bool value = false; };

        template<>
        struct IsDouble<double> { static constexpr bool value = true; };
        // ------


        template<typename Tx, size_t n>
        void selectFunction(void)
        {
            
        }

    }





    template<UfDetails::UniformAllowedType Head, UfDetails::UniformAllowedType... Args>
    void uniform(GLuint loc, Head&& head, Args&&... args)
    {
        RUBY_STATIC_ASSERT(sizeof...(args) <= 3, "Uniform can only receive maximum 4 elements.");   

    }


    template<UfDetails::UniformAllowedType Tx>
    void uniform(GLuint loc, const RubyVector<Tx>& vector)
    {
        RUBY_ASSERT(vector.size() <= 4 && "Uniform can only receive maximum 4 elements.")

        
    }


}


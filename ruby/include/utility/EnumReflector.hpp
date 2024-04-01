#pragma once

#include <StdInc.hpp>
#include <utility/Definitions.hpp>


namespace Ruby 
{
    namespace Details::Enum
    {
        struct Enumiration
        {

        };

        std::optional<i32> getValue(cstr strValues, i32& pos);
        std::optional<RubyString> getField(cstr strValues, i32& pos);
    }


    class EnumReflector
    {
    public:




    private:
        EnumReflector(const i32* values, i32 valuesNumber, cstr enumName, cstr strValues);

    };
}


#define RUBY_CREATE_ENUM(enumName, type, ...)
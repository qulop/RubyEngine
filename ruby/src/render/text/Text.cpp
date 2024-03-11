#include <render/text/Text.hpp>


namespace Ruby
{
    void Text::Display(u32 x, u32 y)
    {
        
    }



    Text& Text::operator=(const RubyString& msg)
    {
        this->msg = msg;

        return *this;
    }

    Text& Text::operator=(RubyString&& msg)
    {
        this->msg = std::move(msg);

        return *this;
    }


}
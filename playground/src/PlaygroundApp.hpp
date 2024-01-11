#include <RubyEngine.hpp>


class Playground final : public Ruby::RubyApp
{
public:
    Playground(Ruby::VideoAttr& va) :
        RubyApp(va)
    {}

    void Update(void) override
    {
        // Write your code here
    }

    virtual ~Playground()
    {}
};

#include <RubyEngine.hpp>


class Playground final : public Ruby::RubyApp
{
public:
    Playground(Ruby::VideoAttr& va, Ruby::Font font) :
        RubyApp(va), msg("Hello Amy, Clara and Vika from RubyEngine!", font)
    {}

    void Update(void) override
    {
        msg.Display(10, 30);
    }

    virtual ~Playground()
    {}

private:
    Ruby::Text msg;
};

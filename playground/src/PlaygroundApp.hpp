#include <RubyEngine.hpp>


class Playground final : public Ruby::RubyApp
{
public:
    Playground(Ruby::VideoAttr& va, Ruby::Font font) :
        RubyApp(va)
    {}

    void Update(void) override
    {
        Ruby::Text text{ font, "Hello Amy, Clara and Vika from RubyEngine!" };

        text.Display(10, 30);
    }

    virtual ~Playground()
    {}

private:
    Ruby::Font font;
};

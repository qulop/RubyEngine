#include <RubyEngine.hpp>

class Playground final : public Ruby::RubyApp
{
public:
    Playground(const Ruby::VideoStruct& va, Ruby::Font font) :
        RubyApp(va), msg("Hello Amy, Clara and Vika from RubyEngine!", font)
    {}

    void Update(void) override
    {}

    virtual ~Playground() = default;

private:
    Ruby::Text msg;
};

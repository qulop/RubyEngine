#include "PlaygroundApp.hpp"
#include <memory>


int main()
{
    Ruby::VideoAttr va { "Playground Demo", true };
    Ruby::Font font { "C:\\Windows\\Fonts\\arial.ttf", 20 };

    Ruby::RubyVector<Ruby::RubyString> a;

    auto playground = std::make_unique<Playground>(va, font);

    if (!playground->Mainloop())
        return 1;
    return 0;
}
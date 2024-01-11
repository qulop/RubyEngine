#include "PlaygroundApp.hpp"
#include <memory>


int main()
{
    Ruby::VideoAttr va { "Playground Demo", true };

    auto playground = std::make_unique<Playground>(va);

    if (!playground->Mainloop())
        return 1;
    return 0;
}
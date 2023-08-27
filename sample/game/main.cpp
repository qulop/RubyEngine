#include "gameapp.hpp"


int main()
{
    Game* game = new Game();

    auto err = game->Run();
    if (err == RUBY_EXIT)
        return 0;

    return 1;
}
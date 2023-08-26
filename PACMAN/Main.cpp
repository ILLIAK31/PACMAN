#include <SFML/Graphics.hpp>
#include "Game.hpp"

int main()
{
    Menu menu;
    Game game(menu);
    game.Run();
    return 0;
}
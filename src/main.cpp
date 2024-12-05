#include <iostream>
#include "../include/Game.hpp"


// TODO: check if Interfaces keep their name if they are not virtual anymore?
int main()
{
    Game game;
    game.setup();
    game.run();
}

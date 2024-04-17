#include "Game.h"

int main() 
{
    Game game;
    for(int i =0; i<10; i++)
        game.addArmy();
    game.printAll();
    return 0;
}
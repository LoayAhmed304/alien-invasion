#include <iostream>
#include "Units/Units.h"
#include "Units/EarthArmy.h"
#include "Units/AlienArmy.h"
#include "Game.h"
#include "randGen.h"


using namespace std;
int main() 
{
    Game game;
    game.simulate();
    game.printAll();
    return 0;
}
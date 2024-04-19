#ifndef GAME_H
#define GAME_H

#include "../Units/Aliens/AlienArmy.h"
#include "../Units/Earth/EarthArmy.h"
#include "../RandomGenerator/randGen.h"
#include <fstream>
using namespace std;

class Game {
private:
	int timestep;
	bool isOver;
	LinkedQueue<Units*> killedList;
	randGen* random;
	EarthArmy* eArmy;
	AlienArmy* aArmy;
public:
	Game();
	void setRandom();	// Reads the input file and initializes randGen object
	void printAll();	// Prints all the lists
	void fight();
	EarthArmy* getEarthArmy();
	AlienArmy* getAlienArmy();
	bool getUnit(unitType, Units*&);
	bool peekUnit(unitType, Units*&);

	int getTimestep();

	void simulate();
	// void exportFile();
};

#endif
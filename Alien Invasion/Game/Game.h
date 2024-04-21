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
	//////////////////////////////
	priQueue<Units*> UML;


public:
	Game();
	void setRandom();	// Reads the input file and initializes randGen object
	void printAll();	// Prints all the lists
	void fight();
	EarthArmy* getEarthArmy();
	AlienArmy* getAlienArmy();
	int getLength(unitType);
	bool getUnit(unitType, Units*&, int = 0);
	bool peekUnit(unitType, Units*&, int = 0);
	int getTimestep();
	void simulate();
	bool getUML(Units*&);
	bool addUnit(Units*&);

	bool kill(Units*&);
	bool toUML(Units*&);

	// void exportFile();
	~Game();
};

#endif
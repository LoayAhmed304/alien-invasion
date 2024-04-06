#ifndef GAME_H
#define GAME_H

#include "Units/Aliens/AlienArmy.h"
#include "Units/Earth/EarthArmy.h"
#include "randGen.h"
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
	void addArmy();		// Adds random army to both armies
	void printAll();	// Prints all the lists
	void simulate();	// Simulation for phase 1.2 test code

	//void exportFile();						// Phase 2
	//void fight(alienArmy*, earthArmy*);		// Phase 2
	//int checkStatus(alienArmy*, earthArmy*);	// Phase 2
};

#endif
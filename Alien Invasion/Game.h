#ifndef GAME_H
#define GAME_H

#include "DataStructures/LinkedQueue.h"
#include "Units/AlienArmy.h"
#include "Units/EarthArmy.h"
#include "Units/Units.h"
#include "randGen.h"
#include <fstream>
class Game {
private:
	int timestep;
	int N;
	bool isOver;
	LinkedQueue<Units*> killedList;
	randGen* random;
	EarthArmy* eArmy;
	AlienArmy* aArmy;

public:
	Game();
	void setRandom(); // Replaced to be loaded in the constructor
	//void exportFile(); // Phase 2
	void addArmy(); //earthArmy
	//void fight(alienArmy*, earthArmy*);	//Phase 2
	//int checkStatus(alienArmy*, earthArmy*);	//Phase 2
	void printAll();
	//void sim();
};

#endif
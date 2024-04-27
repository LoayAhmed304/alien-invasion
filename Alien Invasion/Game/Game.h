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
	string result;
	LinkedQueue<Units*> killedList;
	randGen* random;
	EarthArmy* eArmy;
	AlienArmy* aArmy;
	//////////////////////////////
	priQueue<Units*> UML;
	fstream outputFile;

	int es, et, eg, eh, as, am, ad;


public:
	Game();
	void setRandom();	// Reads the input file and initializes randGen object
	void printAll();	// Prints all the lists
	void fight();
	EarthArmy* getEarthArmy();
	AlienArmy* getAlienArmy();
	int getLength(unitType);
	bool isEmpty(unitType);
	bool getUnit(unitType, Units*&, int = 0);
	bool peekUnit(unitType, Units*&, int = 0);
	int getTimestep();
	bool getUML(Units*&);
	bool updateUML();
	bool addUnit(Units*&);
	int getMonsterIndex();

	void updateFile(Units*);
	void clearOutput();

	bool kill(Units*&);
	bool toUML(Units*&);

	int getDestructed(unitType t);
	int totalUnits(unitType t);

	~Game();
};

#endif
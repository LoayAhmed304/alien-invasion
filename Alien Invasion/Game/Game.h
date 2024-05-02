#ifndef GAME_H
#define GAME_H

#include "../Units/Aliens/AlienArmy.h"
#include "../Units/Earth/EarthArmy.h"
#include "../RandomGenerator/randGen.h"
#include <fstream>
#include <iomanip>
using namespace std;

class Game {
private:
	int timestep;
	bool shots;
  string result;
	LinkedQueue<Units*> killedList;
	randGen* random;
	EarthArmy* eArmy;
	AlienArmy* aArmy;
	//////////////////////////////
	priQueue<Units*> UML;

	fstream outputFile;
	int es, et, eg, eh, as, am, ad;
	int totalEDf, totalEDd, totalEDb, EDfCount;
	int totalADf, totalADd, totalADb, ADfCount;

	string log;

public:
	Game();
	void setRandom();	// Reads the input file and initializes randGen object
	void printAll();	// Prints all the lists
	void fight();
	bool isOver(int i);

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
	
	void updateFile(Units* = nullptr);
	void clearOutput();

	bool kill(Units*&);
	bool toUML(Units*&);

	int getDestructed(unitType t);
	int totalUnits(unitType t);
	float destructedPerc(unitType t);
	float totalEDestructedPerc();
	float totalADestructedPerc();

	void updateEDf(int df);
	void updateEDd(int dd);
	void updateEDb(int db);

	void updateADf(int df);
	void updateADd(int dd);
	void updateADb(int db);

	void calcEAverage(float& df, float& dd, float& db);
	void calcAAverage(float& df, float& dd, float& db);

	void calcEPercentage(float& DfDb, float& DdDb);
	void calcAPercentage(float& DfDb, float& DdDb);
	~Game();
};

#endif
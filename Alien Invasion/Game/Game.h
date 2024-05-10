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
	string result;
	LinkedQueue<Units*> killedList;
	randGen* random;
	EarthArmy* eArmy;
	AlienArmy* aArmy;

	priQueue<Units*> UML;

	fstream outputFile;
	int es, et, eg, eh, as, am, ad;		// Destructed units
	int totalEDf, totalEDd, totalEDb, EDfCount;		// Earth total D(f/d/b)
	int totalADf, totalADd, totalADb, ADfCount;		// Alien total D(f/d/b)

	string log;		// To store the current units fighting and their opponents

public:
	Game();
	void start();
	void setRandom();	// Reads the input file and initializes randGen object
	void printAll();	// Prints all the output screen
	void fight(int c);		// Calls the fight of each army
	bool isOver();	// Checks whether the war is over

	EarthArmy* getEarthArmy();
	AlienArmy* getAlienArmy();

	int getLength(unitType);
	bool isEmpty(unitType);
	bool getUnit(unitType, Units*&);
	bool peekUnit(unitType, Units*&);
	int getTimestep();
	bool getUML(Units*&);
	bool addUnit(Units*&);
	void updateFile(Units* = nullptr);	// Updates the output file
	void prepareOutputFile();		// Clears and sets the output file

	bool kill(Units*&);
	bool toUML(Units*&);
	bool toLog(int = 0,int = 0);
	int getDestructed(unitType t);	// Retruns the number of destructed units
	int totalUnits(unitType t);		// Retruns the destructed + current units
	float destructedPerc(unitType t);		// Calculates the destructed/total percentage

	// Increments the total earth&alien D(f,d,b) and their count
	void updateEDf(int df);
	void updateEDd(int dd);
	void updateEDb(int db);

	void updateADf(int df);
	void updateADd(int dd);
	void updateADb(int db);


	// Calculates the average D(f,d,b) and their percentages for earth and aliens
	void calcEAverage(float& df, float& dd, float& db);
	void calcAAverage(float& df, float& dd, float& db);

	void calcEPercentage(float& DfDb, float& DdDb);
	void calcAPercentage(float& DfDb, float& DdDb);
	~Game();
};

#endif
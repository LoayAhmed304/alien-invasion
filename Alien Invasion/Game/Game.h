#ifndef GAME_H
#define GAME_H

#include "../Units/Aliens/AlienArmy.h"
#include "../Units/Earth/EarthArmy.h"
#include "../Units/Ally/AllyArmy.h"
#include "../RandomGenerator/randGen.h"
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

class Game {
private:
	int timestep;
	string result;
	LinkedQueue<Unit*> killedList;
	randGen* random;
	EarthArmy* eArmy;
	AlienArmy* aArmy;
	AllyArmy* sArmy;

	priQueue<Unit*> UML;

	string inputFileName;
	fstream outputFile;
	int Ues, Uet;
	int es, et, eg, eh, as, am, ad;		// Destructed units

	string log;		// To store the current units fighting and their opponents

public:
	Game();
	void start();
	void setRandom();	// Reads the input file and initializes randGen object
	void printAll();	// Prints all the output screen
	void fight(int);		// Calls the fight of each army
	bool isOver(bool, bool, bool);	// Checks whether the war is over

	EarthArmy* getEarthArmy() const;
	AlienArmy* getAlienArmy() const;
	AllyArmy* getAllyArmy() const;

	int getLength(unitType) const;
	bool isEmpty(unitType) const;
	bool getUnit(unitType, Unit*&) const;
	bool peekUnit(unitType, Unit*&) const;
	int getTimestep() const;
	bool getUML(Unit*&);
	bool addUnit(Unit*&);
	void updateFile(Unit* = nullptr);	// Updates the output file
	void prepareOutputFile();		// Clears and sets the output file

	bool kill(Unit*&);
	bool toUML(Unit*&);
	bool toLog(Unit* = nullptr, Unit* = nullptr, string = "");

	void countUML();

	// Units infection
	bool canInfect() const;
	bool canSpread() const;
	bool spreadInfection();
	void allyArmyNotNeeded();
	bool getRandomES(Unit*&) const;


	void update();
	~Game();
};
#endif
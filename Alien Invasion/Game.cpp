#include "Game.h"

Game::Game(): timestep(1), isOver(false)
{
	eArmy = new EarthArmy;
	aArmy = new AlienArmy;
	setRandom();
}

void Game::setRandom() 
{
	int N, es, et, eg, as, am, ad, probability, epl, eph,
		ehl, ehh, ecl, ech, apl, aph, ahl, ahh, acl, ac;		// Variables to store values from the input file

	fstream inputFile;
	string fileName = "input.txt";
	inputFile.open(fileName, ios::in);
	if (inputFile.is_open()) 
	{
		inputFile >> N >> es >> et >> eg >> as >> am >> ad >> probability;									// Reading first 8 digits
		inputFile >> epl >> eph >> ehl >> ehh >> ecl >> ech >> apl >> aph >> ahl >> ahh >> acl >> ac;

		random = new randGen(N, es, et, eg, as, am, ad, probability, epl, abs(eph),							// Take absolute to any high-value 
			ehl, abs(ehh), ecl, abs(ech), apl, abs(aph), ahl, abs(ahh), acl, abs(ac));						//	to handle the range dash '-'
	}
	else 
	{
		throw std::ios_base::failure("Failed to open file");												// File didn't open properly
	} 
}

void Game::printAll() 
{
	cout << "============== Earth Army Alive Units =============\n";
	eArmy->print();
	cout << endl;
	cout << "============== Alien Army Alive Units =============\n";
	aArmy->print();
	cout << endl;
	cout << "============== Killed/Destructed Units =============\n";
	cout << killedList.length()<< " units [";
	killedList.printAll();
	cout << "]\n";
}

void Game::fight()
{
	eArmy->fight();
	aArmy->fight();
}

bool Game::getUnit(unitType s, Units*& unit)
{
	if(s<alienSoldier)
		return eArmy->getUnit(s, unit);
	return aArmy->getUnit(s, unit);
}

bool Game::peekUnit(unitType s, Units*& unit)
{
	if (s < alienSoldier)
		return eArmy->peekUnit(s, unit);
	return aArmy->peekUnit(s, unit);
}

int Game::getTimestep()
{
	return timestep;
}

void Game::addArmy() 
{
	Units* newBorn;
	int N;
	if (random->probability(N)) {
		for (int i = 0; i < N; i++) {
			newBorn = random->generateAlien(timestep);
			newBorn->setGame(this);
			aArmy->addUnit(newBorn);
		}
	}
	if (random->probability(N)) {
		for (int i = 0; i < N; i++) {
			newBorn = random->generateEarth(timestep);
			newBorn->setGame(this);
			eArmy->AddUnit(newBorn);
		}
	}
}

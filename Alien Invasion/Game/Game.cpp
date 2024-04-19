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
			ehl, abs(ehh), ecl, abs(ech), apl, abs(aph), ahl, abs(ahh), acl, abs(ac), this);						//	to handle the range dash '-'
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

EarthArmy* Game::getEarthArmy()
{
	return eArmy;
}

AlienArmy* Game::getAlienArmy()
{
	return aArmy;
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

void Game::simulate()
{
	LinkedQueue<Units*> tempList;		// To store units temporarily
	Units* tempUnit = nullptr;			// To point to a unit temporarily
	for (int i = 0; i < 50; ++i)			// 50 timesteps for phase 1.2 test code
	{
		random->addUnits();
		int x = random->generateNum();
		cout << "Current Timestep " << timestep++ << "\n";
		cout << "\n\tProbability: " << x << endl;


		if (x < 10)
		{
			if (!eArmy->isEmpty(earthSoldier))		// if no soldiers found do nothing
			{
				eArmy->getUnit(earthSoldier, tempUnit);
				eArmy->addUnit(tempUnit);
			}
		}
		else if (x < 20)
		{
			if (!eArmy->isEmpty(earthTank))		// if no tanks found do nothing
			{
				eArmy->getUnit(earthTank, tempUnit);
				killedList.enqueue(tempUnit);
			}
		}
		else if (x < 30)
		{
			if (!eArmy->isEmpty(earthGunnery))		// if no Gunneries found do nothing
			{
				eArmy->getUnit(earthGunnery, tempUnit);
				tempUnit->getAttacked(tempUnit->getCurHealth() / 2);
				eArmy->addUnit(tempUnit);
			}
		}
		else if (x < 40)
		{
			if (aArmy->length(alienSoldier) >= 5)		// if soldiers are less than 5 do nothing
			{
				for (int i = 0; i < 5; ++i)
				{
					aArmy->getUnit(alienSoldier, tempUnit);
					tempUnit->getAttacked(tempUnit->getCurHealth() / 3);
					tempList.enqueue(tempUnit);
				}
				for (int i = 0; i < 5; ++i)
				{
					tempList.dequeue(tempUnit);
					aArmy->addUnit(tempUnit);
				}
			}
		}
		else if (x < 50)
		{
			if (aArmy->length(alienMonster) >= 5)		// if monsters are less than 5 do nothing
			{
				for (int i = 0; i < 5; ++i)
				{
					aArmy->getUnit(alienMonster, tempUnit, random->getMonsterIndex(aArmy->length(alienMonster)));
					tempList.enqueue(tempUnit);
				}
				for (int i = 0; i < 5; ++i)
				{
					tempList.dequeue(tempUnit);
					aArmy->addUnit(tempUnit);
				}
			}
		}
		else if (x < 60)					// if drones are less than 6 do nothing
		{
			if (aArmy->length(alienDrone) >= 6)
			{
				for (int i = 0; i < 6; ++i)
				{
					aArmy->getUnit(alienDrone, tempUnit);
					tempList.enqueue(tempUnit);
				}
				for (int i = 0; i < 6; ++i)
				{
					tempList.dequeue(tempUnit);
					killedList.enqueue(tempUnit);
				}
			}
		}
		tempUnit = nullptr;
		printAll();
		system("pause");
		cout << endl;
	}
}

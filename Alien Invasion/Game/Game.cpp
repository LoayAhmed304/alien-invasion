#include "Game.h"
Game::Game() : timestep(1), isOver(false), shots(true)
{
	eArmy = new EarthArmy;
	aArmy = new AlienArmy;
	setRandom();
}

void Game::setRandom()
{
	int N, es, et, eg, eh, as, am, ad, probability, epl, eph,
		ehl, ehh, ecl, ech, apl, aph, ahl, ahh, acl, ac;		// Variables to store values from the input file

	fstream inputFile;
	string fileName = "input.txt";
	inputFile.open(fileName, ios::in);
	if (inputFile.is_open())
	{
		inputFile >> N >> es >> et >> eg >> eh >> as >> am >> ad >> probability;									// Reading first 8 digits
		inputFile >> epl >> eph >> ehl >> ehh >> ecl >> ech >> apl >> aph >> ahl >> ahh >> acl >> ac;

		random = new randGen(N, es, et, eg, eh, as, am, ad, probability, epl, abs(eph),							// Take absolute to any high-value 
			ehl, abs(ehh), ecl, abs(ech), apl, abs(aph), ahl, abs(ahh), acl, abs(ac), this);						//	to handle the range dash '-'
	}
	else
	{
		throw std::ios_base::failure("Failed to open file");												// File didn't open properly
	}
}

void Game::printAll()
{

	cout << "\n\033[1;36m============== Earth Army Alive Units ============\n";
	eArmy->print();
	cout << endl;

	cout << "\033[1;32m============== Alien Army Alive Units ==============\n";
	aArmy->print();
	cout << endl;

	cout << "\033[1;35m============== Units fighting at current step =============\n";
	cout << log;
	log.clear();
	cout << endl;

	cout << "\033[1;31m============== Killed/Destructed Units =============\n";
	cout << killedList.length() << " units [";
	killedList.printAll();
	cout << "]\n\n";

	cout << "\033[1;33m============== UML =============\n";
	cout << UML.length() << " units [";
	UML.printAll();
	cout << "]\n\n\033[0m";

}

EarthArmy* Game::getEarthArmy()
{
	return eArmy;
}

AlienArmy* Game::getAlienArmy()
{
	return aArmy;
}

int Game::getLength(unitType s)
{
	if (s < alienSoldier)
		return eArmy->getLength(s);
	if(s<alienArmy)
		return aArmy->getLength(s);
}

bool Game::isEmpty(unitType s)
{
	if (s < alienSoldier)
		return eArmy->isEmpty(s);
	return aArmy->isEmpty(s);
}

bool Game::getUnit(unitType s, Units*& unit, int m)
{
	if (s < alienSoldier)
		return eArmy->getUnit(s, unit);
	return aArmy->getUnit(s, unit, m);
}

bool Game::addUnit(Units*& unit)
{
	if (unit->getType() < alienSoldier)
		return eArmy->addUnit(unit);
	return aArmy->addUnit(unit);
}

int Game::getMonsterIndex()
{
	return (random->getMonsterIndex(aArmy->getLength(alienMonster)));
}

bool Game::totemp(Units* unit)
{
	return temp.enqueue(unit);
}

bool Game::kill(Units*& unit)
{
	return killedList.enqueue(unit);;
}

bool Game::toUML(Units*& unit)
{

	if (unit->getType() == earthSoldier)
	{
		unit->enterUML();
		UML.enqueue(unit, -unit->getCurHealth());
	}
	else if (unit->getType() == earthTank)
	{
		unit->enterUML();
		UML.enqueue(unit, -INT_MAX);
	}
	return true;
}

bool Game::peekUnit(unitType s, Units*& unit, int m)
{
	if (s < alienSoldier)
		return eArmy->peekUnit(s, unit);
	return aArmy->peekUnit(s, unit, m);
}

int Game::getTimestep()
{
	return timestep;
}

void Game::fight()
{
	int i = 0;
	while (!isOver)
	{
		cout << "Current Timestep " << timestep++ << endl;

		random->addUnits();
		printAll();

		eArmy->fight(log);
		aArmy->fight(log, getMonsterIndex());

		updateUML();

		if (i > 40)				// Start checking for result
		{
			if ((eArmy->isEmpty(earthArmy) && aArmy->isEmpty(alienArmy)) || !shots)
			{
				result = "Tie";
				isOver = true;
			}
			else
			{
				if (eArmy->isEmpty(earthArmy))
				{
					result = "Aliens";
					isOver = true;
				}
				if (aArmy->isEmpty(alienArmy))
				{
					result = "Earth";
					isOver = true;
				}
			}
		}
		system("pause");
		cout << endl;
		++i;
	}
}

bool Game::getUML(Units*& unit)
{
	int p;
	if (UML.dequeue(unit, p))
		return true;
	return false;
}

bool Game::updateUML()
{
	Units* unit;
	int p;
	priQueue<Units*> temp;
	while (UML.dequeue(unit,p))
	{
		temp.enqueue(unit, p);
	}
	while (temp.dequeue(unit, p))
	{
		unit->insideUML();
		UML.enqueue(unit, p);
	}
	return false;
}
Game::~Game()
{
	delete eArmy;
	delete aArmy;
	delete random;
	while (!killedList.isEmpty())
	{
		Units* temp;
		killedList.dequeue(temp);
		delete temp;
	}
}

#include "Game.h"
Game::Game() : timestep(1), isOver(false), as(0), am(0), ad(0), es(0), eg(0), et(0), eh(0)
{
	eArmy = new EarthArmy;
	aArmy = new AlienArmy;
	setRandom();
	clearOutput();
}

void Game::clearOutput()
{
	outputFile.open("output.txt", ios::out | ios::trunc);
	outputFile.close();
	outputFile.open("output.txt", ios::out);
	outputFile << "Td \t\tID \t\tTj \t\tDf \t\tDd \t\tDb\n\n";
	outputFile.close();
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

void Game::updateFile(Units* unit)
{
	string fileName = "output.txt";
	outputFile.open("output.txt", ios::app);
	if (outputFile.is_open())
	{
		int Td, ID, Tj, Df, Dd, Db;
		Td = unit->getTd();
		ID = unit->getID();
		Tj = unit->getTj();
		Df = unit->getDf();
		Dd = unit->getDd();
		Db = unit->getDb();

		outputFile << Td << "\t\t" << ID << "\t\t" << Tj << "\t\t" << Df << "\t\t" << Dd << "\t\t" << Db << "\n";
		
		if (isOver)
		{
			outputFile << "Battle Result: " << result << endl;
			outputFile << "Earth Army: \n";
			
		}
		outputFile.close();
	}
	else
	{
		throw std::ios_base::failure("Failed to create file");
	}
}

void Game::printAll()
{

	cout << "\n\033[1;36m============== Earth Army Alive Units =============\n";
	eArmy->print();
	cout << endl;

	cout << "\033[1;32m============== Alien Army Alive Units =============\n";
	aArmy->print();
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


bool Game::kill(Units*& unit)
{
	switch(unit->getType())
	{
	case earthSoldier:
		es++;
		break;
	case earthTank:
		et++;
		break;
	case earthGunnery:
		eg++;
		break;
	case alienSoldier:
		as++;
		break;
	case alienMonster:
		am++;
		break;
	case alienDrone:
		ad++;
		break;
	case earthHeal:
		eh++;
		break;
	}
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

int Game::getDestructed(unitType t)
{
	switch (t)
	{
	case alienSoldier:
		return as;
	case alienMonster:
		return am;
	case alienDrone:
		return ad;
	case earthSoldier:
		return es;
	case earthGunnery:
		return eg;
	case earthTank:
		return et;
	case earthHeal:
		return eh;
	}
}

int Game::totalUnits(unitType t)
{
	switch (t)
	{
	case earthSoldier:
		return getLength(earthSoldier) + getDestructed(earthSoldier);
	case earthGunnery:
		return getLength(earthGunnery) + getDestructed(earthGunnery);
	case earthTank:
		return getLength(earthTank) + getDestructed(earthTank);
	case earthHeal:
		return getLength(earthHeal) + getDestructed(earthHeal);
	case alienSoldier:
		return getLength(alienSoldier) + getDestructed(alienSoldier);
	case alienDrone:
		return getLength(alienDrone) + getDestructed(alienDrone);
	case alienMonster:
		return getLength(alienMonster) + getDestructed(alienMonster);
	}
}

float Game::destructedPerc(unitType t)
{
	switch (t)
	{
	case earthSoldier: 
		return float(getDestructed(earthSoldier)) / totalUnits(earthSoldier);
	case earthGunnery:
		return float(getDestructed(earthGunnery)) / totalUnits(earthGunnery);
	case earthTank:
		return float(getDestructed(earthTank)) / totalUnits(earthTank);
	case earthHeal:
		return float(getDestructed(earthHeal)) / totalUnits(earthHeal);
	case alienSoldier:
		return float(getDestructed(alienSoldier)) / totalUnits(alienSoldier);
	case alienDrone:
		return float(getDestructed(alienDrone)) / totalUnits(alienDrone);
	case alienMonster:
		return float(getDestructed(alienMonster)) / totalUnits(alienMonster);
	}
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
	while (i < 1000)
	{
		cout << "Current Timestep " << timestep++ << endl;

		random->addUnits();
		printAll();

		eArmy->fight();
		aArmy->fight(getMonsterIndex());

		updateUML();
		system("pause");
		cout << endl;
		i++;
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

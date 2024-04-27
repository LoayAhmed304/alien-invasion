#include "Game.h"
Game::Game() : timestep(1), isOver(false), as(0), am(0), ad(0), es(0), eg(0), et(0), eh(0), totalEDf(0), totalEDd(0), totalEDb(0), EDfCount(0),
				totalADf(0), totalADd(0), totalADb(0), ADfCount(0)
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
		if (unit)
		{
			int Td, ID, Tj, Df, Dd, Db;
			Td = unit->getTd();
			ID = unit->getID();
			Tj = unit->getTj();
			Df = unit->getDf();
			Dd = unit->getDd();
			Db = unit->getDb();

			outputFile << Td << "\t\t" << ID << "\t\t" << Tj << "\t\t" << Df << "\t\t" << Dd << "\t\t" << Db << "\n";
		}
		else
		{
			outputFile << "\nBattle Result: " << result << endl << endl;
			float dfdb, dddb, adf, add, adb;
			////////////////// Earth Army Statistics //////////////////////////
			outputFile << "Earth Army: \n";

			outputFile << "\tTotal number of units:\n";
			outputFile << "\t\tES: " << totalUnits(earthSoldier);
			outputFile << "\tET: " << totalUnits(earthTank);
			outputFile << "\tEG: " << totalUnits(earthGunnery);
			outputFile << "\tEH: " << totalUnits(earthHeal) << endl;


			outputFile << "\tUnits Destruction %: \n";
			outputFile << "\t\tES: " << std::setprecision(3) << destructedPerc(earthSoldier) * 100 << "%";
			outputFile << "\tET: " << std::setprecision(3) << destructedPerc(earthTank) * 100 << "%";
			outputFile << "\tEG: " << std::setprecision(3) << destructedPerc(earthGunnery) * 100 << "%";
			outputFile << "\tEH: " << std::setprecision(3) << destructedPerc(earthHeal) * 100 << "%\n";


			outputFile << "\tUnits Relative Destruction %: \n\t\t";
			outputFile << std::setprecision(4) << totalEDestructedPerc() * 100 << "%\n";


			calcEAverage(adf, add, adb);
			outputFile << "\tAverage values of: \n";
			outputFile << "\t\tDf: " << std::setprecision(2) << adf << "\tDd: " << add << "\tDb: " << adb << "\n";


			calcEPercentage(dfdb, dddb);
			outputFile << "\t\tDf/Db%: " << setprecision(4) << dfdb * 100 << "%";
			outputFile << "\tDd/Db%: " << setprecision(4) << dddb * 100 << "%\n\n";

			////////////////// Alien Army Statistics //////////////////////////
			outputFile << "Alien Army: \n";

			outputFile << "\tTotal number of units:\n";
			outputFile << "\t\tAS: " << totalUnits(alienSoldier);
			outputFile << "\tAM: " << totalUnits(alienMonster);
			outputFile << "\tAD: " << totalUnits(alienDrone) << endl;


			outputFile << "\tUnits Destruction %: \n";
			outputFile << "\t\tAS: " << std::setprecision(3) << destructedPerc(alienSoldier) * 100 << "%";
			outputFile << "\tAM: " << std::setprecision(3) << destructedPerc(alienMonster) * 100 << "%";
			outputFile << "\tAD: " << std::setprecision(3) << destructedPerc(alienDrone) * 100 << "%\n";


			outputFile << "\tUnits Relative Destruction %: \n\t\t";
			outputFile << std::setprecision(4) << totalADestructedPerc() * 100 << "%\n";


			calcAAverage(adf, add, adb);
			outputFile << "\tAverage values of: \n";
			outputFile << "\t\tDf: " << std::setprecision(2) << adf << "\tDd: " << add << "\tDb: " << adb << "\n";


			calcAPercentage(dfdb, dddb);
			outputFile << "\t\tDf/Db%: " << setprecision(4) << dfdb * 100 << "%";
			outputFile << "\tDd/Db%: " << setprecision(4) << dddb * 100 << "%\n\n";
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

	cout << "\n\033[1;36m============== Earth Army Alive Units ============\n";
	eArmy->print();
	cout << endl;

	cout << "\033[1;32m============== Alien Army Alive Units ==============\n";
	aArmy->print();
	cout << endl;

	cout << "\033[1;35m============== Units fighting at current step =============\n";
	shots = printtemp();
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
	float n = 0, d = 1;
	switch (t)
	{
	case earthSoldier: 
		n = float(getDestructed(earthSoldier));
		d = totalUnits(earthSoldier);
		break;
	case earthGunnery:
		n = (getDestructed(earthGunnery));
		d= totalUnits(earthGunnery);
		break;
	case earthTank:
		n = (getDestructed(earthTank));
		d= totalUnits(earthTank);
		break;
	case earthHeal:
		n = (getDestructed(earthHeal)); 
		d= totalUnits(earthHeal);
		break;
	case alienSoldier:
		n = (getDestructed(alienSoldier));
		d= totalUnits(alienSoldier);
		break;
	case alienDrone:
		n = (getDestructed(alienDrone));
		d= totalUnits(alienDrone);
		break;
	case alienMonster:
		n = (getDestructed(alienMonster));
		d= totalUnits(alienMonster);
		break;
	}
	if (d == 0) return 0;
	return n / d;
}

float Game::totalEDestructedPerc()
{
	float d = es + eh + eg + et;
	float n = Units::getTotalUnits(earthArmy);
	if (n == 0) return 0;
	return d/n;
}

float Game::totalADestructedPerc()
{
	float d = float(as + am + ad);
	float n = Units::getTotalUnits(alienArmy);
	if (n == 0) return 0;
	return d / n;
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
		/////////	To test the output file		//////////////////
		if (i == 2)
		{
			updateFile(nullptr);
			break;
		}
		//////////////////////////////////////////////////////////
		eArmy->fight();
		aArmy->fight(getMonsterIndex());

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
bool Game::printtemp()
{
	Units* unit;
	if (temp.dequeue(unit))
	{
		if (unit != nullptr)
			if (unit->getType() == earthSoldier)
			{
				cout << unit->getID() << " shots [";
				temp.dequeue(unit);
				cout << unit->getID();
				temp.dequeue(unit);
				while (unit != nullptr)
				{
					cout << " ," << unit->getID();
					temp.dequeue(unit);

				}
				cout << "]\n";
				temp.dequeue(unit);
			}
		if (unit != nullptr)
			if (unit->getType() == earthTank)
			{
				cout << unit->getID() << " shots [";
				temp.dequeue(unit);
				cout << unit->getID();
				while (unit != nullptr)
				{
					temp.dequeue(unit);
					if (unit != nullptr)
						cout << " ," << unit->getID();
				}
				cout << "]\n";
				temp.dequeue(unit);
			}
		if (unit != nullptr)
			if (unit->getType() == earthGunnery)
			{
				cout << unit->getID() << " shots [";
				temp.dequeue(unit);
				cout << unit->getID();
				while (unit != nullptr)
				{

					temp.dequeue(unit);
					if (unit != nullptr)
						cout << " ," << unit->getID();
				}
				cout << "]\n";
				temp.dequeue(unit);
			}
		if (unit != nullptr)
			if (unit->getType() == alienSoldier)
			{
				cout << unit->getID() << " shots [";
				temp.dequeue(unit);
				cout << unit->getID();
				while (unit != nullptr)
				{

					temp.dequeue(unit);
					if (unit != nullptr)
						cout << " ," << unit->getID();
				}
				cout << "]\n";
				temp.dequeue(unit);
			}
		if (unit != nullptr)
			if (unit->getType() == alienMonster)
			{
				cout << unit->getID() << " shots [";
				temp.dequeue(unit);
				cout << unit->getID();
				while (unit != nullptr)
				{

					temp.dequeue(unit);
					if (unit != nullptr)
						cout << " ," << unit->getID();
				}
				cout << "]\n";
				temp.dequeue(unit);
			}
		if (unit != nullptr)
			if (unit->getType() == alienDrone)
			{
				cout << unit->getID() << " shots [";
				temp.dequeue(unit);
				cout << unit->getID();
				while (unit != nullptr)
				{

					temp.dequeue(unit);
					if (unit != nullptr)
						cout << " ," << unit->getID();
				}
				cout << "]\n";
				temp.dequeue(unit);
			}
		if (unit != nullptr)
			if (unit->getType() == alienDrone)
			{
				cout << unit->getID() << " shots [";
				temp.dequeue(unit);
				cout << unit->getID();
				while (unit != nullptr)
				{

					temp.dequeue(unit);
					if (unit != nullptr)
						cout << " ," << unit->getID();
				}
				cout << "]\n";
				temp.dequeue(unit);
			}
		return true;
	}
	return false;
}

void Game::updateEDf(int df)
{
	totalEDf += df;
	++EDfCount;
}

void Game::updateEDd(int dd)
{
	totalEDd += dd;
}

void Game::updateEDb(int db)
{
	totalEDb += db;
}

void Game::updateADf(int df)
{
	totalADf += df;
	++ADfCount;
}

void Game::updateADd(int dd)
{
	totalADd += dd;
}

void Game::updateADb(int db)
{
	totalADb += db;
}

void Game::calcEAverage(float& df, float& dd, float& db)
{
	float d = float(getDestructed(earthSoldier) + getDestructed(earthGunnery) + getDestructed(earthTank));
	if (d == 0)
		dd = db = 0;
	else
	{
		dd = float(totalEDd) / d;
		db = float(totalEDb) / d;
	}
	if (!EDfCount)
		df = 0;
	else
		df = float(totalEDf) / EDfCount;
}

void Game::calcAAverage(float& df, float& dd, float& db)	// 170 85
{
	float d = float(getDestructed(alienSoldier) + getDestructed(alienDrone) + getDestructed(alienMonster));
	if (!ADfCount) 
		df = 0;
	else
		df = float(totalADf) / ADfCount;
	if (!d)
		dd = db = 0;
	else
	{
		dd = float(totalADd) / d;
		db = float(totalADb) / d;
	}
}

void Game::calcEPercentage(float& DfDb, float& DdDb)
{
	if (!totalEDb)
		DfDb = DdDb = 0;
	else
	{
		DfDb = float(totalEDf) / totalEDb;
		DdDb = float(totalEDd) / totalEDb;
	}
}

void Game::calcAPercentage(float& DfDb, float& DdDb)
{
	if (!totalADb)
		DfDb = DdDb = 0;
	else
	{
		DfDb = float(totalADf) / totalADb;
		DdDb = float(totalADd) / totalADb;
	}
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

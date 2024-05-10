#include "Game.h"
Game::Game() : timestep(1), as(0), am(0), ad(0), es(0), eg(0), et(0), eh(0),Ues(0), Uet(0), totalEDf(0), totalEDd(0), totalEDb(0), EDfCount(0),
				totalADf(0), totalADd(0), totalADb(0), ADfCount(0)
{
	eArmy = new EarthArmy;
	aArmy = new AlienArmy;
	setRandom();
	prepareOutputFile();
}

void Game::start()
{
	int choice;
	do {
		cout << "==================Pick Mode==================\n1)Silent Mode\n2)Interactive Mode\n";
		cin >> choice;
	} while (choice != 1 && choice != 2);
	if (choice == 1)
		cout << "Silent Mode\nSimulation Starts...\n";
	fight(choice);
	if (choice == 1)
		cout << "Simulation ends, Output file is created\n";
}

void Game::prepareOutputFile()
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
			outputFile << unit->getTd() << "\t\t" << unit << "\t\t" << unit->getTj() << "\t\t" 
				<< unit->getDf() << "\t\t" << unit->getDd() << "\t\t" << unit->getDb() << "\n";
		}
		else
		{
			outputFile << "\nBattle Result: " << result << endl << endl;
			float dfdb, dddb, adf, add, adb;
			////////////////// Earth Army Statistics //////////////////////////
			outputFile << "Earth Army: \n";
			int e=0, t=0;
			countUML(e, t);
			outputFile << "\tTotal number of units:\n";
			outputFile << "\t\tES: " << getLength(earthSoldier) + es + e;
			outputFile << "\tET: " << getLength(earthTank) + et + t;
			outputFile << "\tEG: " << getLength(earthGunnery) + eg;
			outputFile << "\tEH: " << getLength(earthHeal) + eh << endl;


			outputFile << "\tUnits Destruction %: \n";
			outputFile << "\t\tES: " << std::setprecision(3) << destructedPerc(earthSoldier) * 100 << "%";
			outputFile << "\tET: " << std::setprecision(3) << destructedPerc(earthTank) * 100 << "%";
			outputFile << "\tEG: " << std::setprecision(3) << destructedPerc(earthGunnery) * 100 << "%";
			outputFile << "\tEH: " << std::setprecision(3) << destructedPerc(earthHeal) * 100 << "%\n";


			outputFile << "\tUnits Relative Destruction %: \n\t\t";
			outputFile << std::setprecision(4) << destructedPerc(earthArmy) * 100 << "%\n";


			calcEAverage(adf, add, adb);
			outputFile << "\tAverage values of: \n";
			outputFile << "\t\tDf: " << std::setprecision(2) << adf << "\tDd: " << add << "\tDb: " << adb << "\n";


			calcEPercentage(dfdb, dddb);
			outputFile << "\t\tDf/Db%: " << setprecision(4) << dfdb * 100 << "%";
			outputFile << "\tDd/Db%: " << setprecision(4) << dddb * 100 << "%\n";

			outputFile << "\tHealed Percentage: " << setprecision(4) << calcHealedPercentage() *100 << "%\n\n";

			////////////////// Alien Army Statistics //////////////////////////
			outputFile << "Alien Army: \n";

			outputFile << "\tTotal number of units:\n";
			outputFile << "\t\tAS: " << getLength(alienSoldier) + as;
			outputFile << "\tAM: " << getLength(alienMonster) + am;
			outputFile << "\tAD: " << getLength(alienDrone) + ad << endl;


			outputFile << "\tUnits Destruction %: \n";
			outputFile << "\t\tAS: " << std::setprecision(3) << destructedPerc(alienSoldier) * 100 << "%";
			outputFile << "\tAM: " << std::setprecision(3) << destructedPerc(alienMonster) * 100 << "%";
			outputFile << "\tAD: " << std::setprecision(3) << destructedPerc(alienDrone) * 100 << "%\n";


			outputFile << "\tUnits Relative Destruction %: \n\t\t";
			outputFile << std::setprecision(4) << destructedPerc(alienArmy) * 100 << "%\n";


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

	cout << "Current Timestep " << timestep << endl;

	if (Units::getTotalUnits(earthArmy) >= 999)
		cout << "Earth units limit exceeded\n";
	if (Units::getTotalUnits(alienArmy) >= 999)
		cout << "Alien units limit exceeded\n";

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

	system("pause");
	cout << endl;
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

bool Game::getUnit(unitType s, Units*& unit)
{
	if (s < alienSoldier)
		return eArmy->getUnit(s, unit);
	return aArmy->getUnit(s, unit);
}

bool Game::addUnit(Units*& unit)
{
	if (unit->getType() < alienSoldier)
		return eArmy->addUnit(unit);
	return aArmy->addUnit(unit);
}

bool Game::isOver()
{
	if (timestep >= 40)
	{
		
		if (eArmy->isEmpty(earthArmy))
		{
			result = "Loss";
			updateFile();
			return true;
		}
		else if (aArmy->isEmpty(alienArmy))
		{
			result = "Win";
			updateFile();
			return true;
		}
		else if ((eArmy->isEmpty(earthArmy) && aArmy->isEmpty(alienArmy)) || !log.size())
		{
			result = "Tie";
			updateFile();
			return true;
		}
	}
	return false;
}

bool Game::kill(Units*& unit)
{
	switch (unit->getType())
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
	updateFile(unit);
	return killedList.enqueue(unit);
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
		UML.enqueue(unit, INT_MIN);
	}
	return true;
}

bool Game::toLog(int a ,int b)
{
	if(a && b)
		log = log + to_string(a) + " shots [" + to_string(b);
	else if(a)
		log = log + ", " + to_string(a);
	else
		log = log + "]\n";

	return false;
}


float Game::destructedPerc(unitType t)
{
	float n = 0, d = 1;
	switch (t)
	{
	case earthSoldier:
		n = float(es);
		d = getLength(earthSoldier) + es;
		break;
	case earthGunnery:
		n = (eg);
		d = getLength(earthGunnery) + eg;
		break;
	case earthTank:
		n = (et);
		d = getLength(earthTank) + et;
		break;
	case earthHeal:
		n = (eh);
		d = getLength(earthHeal) + eh;
		break;
	case alienSoldier:
		n = (as);
		d = getLength(alienSoldier) + as;
		break;
	case alienDrone:
		n = (ad);
		d = getLength(alienDrone) + ad;
		break;
	case alienMonster:
		n = (am);
		d = getLength(alienMonster) + am;
		break;
	case earthArmy:
		n = float(es + et + eg + eh);
		d = Units::getTotalUnits(earthArmy);
		break;
	case alienArmy:
		n = float(as + ad + am);
		d = Units::getTotalUnits(alienArmy);
		break;
	}
	if (d == 0) return 0;
	return n / d;
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

void Game::fight(int c)
{
	bool over = false;
	while (!over)
	{
		random->addUnits();						// Adding units to both armies

		eArmy->fight();						// Calling both armies to fight one another
		aArmy->fight();

		over = isOver();				// Checking if it's over

		if(c==2)
			printAll();			// Printing the output screen
		++timestep;
	}
}

bool Game::getUML(Units*& unit)
{
	int p;
	if (UML.dequeue(unit, p))
		return true;
	return false;
}

void Game::updateEDf(int df)
{
	totalEDf += df;
	++EDfCount;
}

void Game::updateEdb(Units* unit)
{
	totalEDd += unit->getDd();
	totalEDb += unit->getDb();
}

void Game::updateADf(int df)
{
	totalADf += df;
	++ADfCount;
}

void Game::updateAdb(Units* unit)
{
	totalADd += unit->getDd();
	totalADb += unit->getDb();
}

void Game::updateHealed()
{
	++healed;
}

void Game::countUML(int& es, int& et)
{
	Units* unit = nullptr;
	int n;
	while (UML.dequeue(unit, n))
	{
		if (unit->getType() == earthSoldier)
			++Ues;
		else
			++Uet;
	}
}

void Game::calcEAverage(float& df, float& dd, float& db)
{
	float d = float(es + eg + et + eh);
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
	float d = float(as + ad + am);
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

float Game::calcHealedPercentage()
{
	float d = float(healed);
	float n = Units::getTotalUnits(earthArmy);
	return (n == 0) ? 0 : d / n;
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
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
			countUML();
			outputFile << "\nBattle Result: " << result << endl << endl;
			float dfdb, dddb;
			////////////////// Earth Army Statistics //////////////////////////
			outputFile << "Earth Army: \n";
			
			outputFile << "\tTotal number of units:\n";
			outputFile << "\t\tES: " << getLength(earthSoldier) + es + Ues;
			outputFile << "\tET: " << getLength(earthTank) + et + Uet;
			outputFile << "\tEG: " << getLength(earthGunnery) + eg;
			outputFile << "\tEH: " << getLength(earthHeal) + eh << endl;


			outputFile << "\tUnits Destruction %: \n";
			outputFile << "\t\tES: " << std::setprecision(3) << ((getLength(earthSoldier) + es + Ues != 0) ? float(es) / (getLength(earthSoldier) + es + Ues) * 100 : 0) << "%";
			outputFile << "\tET: " << std::setprecision(3) << ((getLength(earthTank) + et + Uet != 0) ? float(et) / (getLength(earthTank) + et + Uet) * 100 : 0) << "%";
			outputFile << "\tEG: " << std::setprecision(3) << ((getLength(earthGunnery) + eg != 0) ? float(eg) / (getLength(earthGunnery) + eg) * 100 : 0)  << "%";
			outputFile << "\tEH: " << std::setprecision(3) << ((getLength(earthHeal) + eh != 0) ? float(eh) / (getLength(earthHeal) + eh) * 100 : 0) << "%\n";


			outputFile << "\tUnits Relative Destruction %: \n\t\t";
			outputFile << std::setprecision(4) << float(es + et + eg + eh) / Units::getTotalUnits(earthArmy) * 100 << "%\n";


			outputFile << "\tAverage values of: \n\t";
			outputFile << "\tDf: " << std::setprecision(2) << ((EDfCount != 0) ? float(totalEDf) / EDfCount : 0);
			outputFile << "\tDd: " << std::setprecision(2) << float(totalEDd) / (es + eg + et + eh);
			outputFile << "\tDb: " << std::setprecision(2) << float(totalEDb) / (es + eg + et + eh) << "\n\t";


			outputFile << "\tDf/Db%: " << setprecision(4) << float(totalEDf) / totalEDb * 100 << "%";
			outputFile << "\tDd/Db%: " << setprecision(4) << float(totalEDd) / totalEDb * 100 << "%\n";

			outputFile << "\tHealed Percentage: " << setprecision(4) << calcHealedPercentage() *100 << "%\n\n";

			////////////////// Alien Army Statistics //////////////////////////
			outputFile << "Alien Army: \n";

			outputFile << "\tTotal number of units:\n";
			outputFile << "\t\tAS: " << getLength(alienSoldier) + as;
			outputFile << "\tAM: " << getLength(alienMonster) + am;
			outputFile << "\tAD: " << getLength(alienDrone) + ad << endl;


			outputFile << "\tUnits Destruction %: \n";
			outputFile << "\t\tAS: " << std::setprecision(3) << ((getLength(alienSoldier) + as != 0) ? float(as) / (getLength(alienSoldier) + as) * 100 : 0) << "%";
			outputFile << "\tAM: " << std::setprecision(3) << ((getLength(alienMonster) + am != 0) ? float(am) / (getLength(alienMonster) + am) * 100 : 0) << "%";
			outputFile << "\tAD: " << std::setprecision(3) << ((getLength(alienDrone) + ad != 0) ? float(ad) / (getLength(alienDrone) + ad) * 100 : 0) << "%\n";


			outputFile << "\tUnits Relative Destruction %: \n\t\t";
			outputFile << std::setprecision(4) << float(as + am + ad) / Units::getTotalUnits(alienArmy) * 100 << "%\n";


			outputFile << "\tAverage values of: \n\t";
			outputFile << "\tDf: " << std::setprecision(2) << float(totalADf) / ADfCount;
			outputFile << "\tDd: " << std::setprecision(2) << float(totalADd) / (as + ad + am);
			outputFile << "\tDb: " << std::setprecision(2) << float(totalADb) / (as + ad + am) << "\n\t";


			outputFile << "\tDf/Db%: " << setprecision(4) << float(totalADf) / totalADb * 100 << "%";
			outputFile << "\tDd/Db%: " << setprecision(4) << float(totalEDd) / totalEDb * 100 << "%\n\n";
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

void Game::countUML()
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
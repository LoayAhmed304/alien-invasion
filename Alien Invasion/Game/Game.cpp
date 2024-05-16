#include "Game.h"
Game::Game() : timestep(1), as(0), am(0), ad(0), es(0), eg(0), et(0), eh(0)
{
	eArmy = new EarthArmy;
	aArmy = new AlienArmy;
	sArmy = new AllyArmy;
	setRandom();
	prepareOutputFile();
}

void Game::start()
{
	do {
		cout << "==================Pick Mode==================\n1)Silent Mode\n2)Interactive Mode\n";
		cin >> playMode;
	} while (playMode != 1 && playMode != 2);
	if (playMode == 1)
		cout << "Silent Mode\nSimulation Starts...\n";
	else
		do {
			cout << "==================Pick Theme==================\n1)Default Mode \n2)Colored Mode \n";
			cin >> playTheme;
		} while (playTheme != 1 && playTheme != 2);

	war(playMode);

	if (playMode == 1)
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
	cout << "Enter the input file name: ";
	cin >> inputFileName;
	if (inputFileName.find(".txt") == string::npos)
		inputFileName += ".txt";
	int N, NS, es, et, eg, eh, as, am, ad, probability, inf, inft, epl, eph,
		ehl, ehh, ecl, ech, apl, aph, ahl, ahh, acl, ach, spl, sph, shl, shh, scl, sch;		// Variables to store values from the input file

	fstream inputFile;
	inputFile.open("Inputs/" + inputFileName, ios::in);
	while (!inputFile.is_open())
	{
		cout << "File doesn't exist.\nEnter the input file name: ";
		cin >> inputFileName;
		if (inputFileName.find(".txt") == string::npos)
			inputFileName += ".txt";
		inputFile.open("Inputs/" + inputFileName, ios::in);
	}

	if (inputFile.is_open())
	{
		inputFile >> N >> NS >> es >> et >> eg >> eh >> as >> am >> ad >> probability >> inf >> inft;									// Reading first 10 digits
		inputFile >> epl >> eph >> ehl >> ehh >> ecl >> ech >> apl >> aph >> ahl >> ahh >> acl >> ach;
		inputFile >> spl >> sph >> shl >> shh >> scl >> sch;
		random = new randGen(N, NS, es, et, eg, eh, as, am, ad, probability, inf, inft, epl, abs(eph),							// Take absolute to any high-value 
			ehl, abs(ehh), ecl, abs(ech), apl, abs(aph), ahl, abs(ahh), acl, abs(ach), spl, abs(sph), shl, abs(shh), scl, abs(sch), this);						//	to handle the range dash '-'
	}
	else
	{
		cout << "File does not exist. Exiting...\n";
		throw std::ios_base::failure("Failed to open file");												// File didn't open properly
	}
}

void Game::updateFile(Unit* unit)
{
	string fileName = "output.txt";
	outputFile.open("output.txt", ios::app);
	if (outputFile.is_open())
	{
		if (unit)
		{
			outputFile << unit->getTd() << "\t\t" << unit->getID() << "\t\t" << unit->getTj() << "\t\t"
				<< unit->getDf() << "\t\t" << unit->getDd() << "\t\t" << unit->getDb() << "\n";
		}
		else
		{
			// Create variables to store the data to be dealt with easier
			float totalEarthUnits = Unit::getTotalUnits(earthArmy);
			float totalDestructedEarthUnits = es + et + eg + eh;
			float totalAlienUnits = Unit::getTotalUnits(alienArmy);
			float totalDestructedAlienUnits = as + ad + am;
			float totalAllyUnits = Unit::getTotalUnits(allyArmy);
			float totalDestructedAllyUnits = su;
			float EDf, EDd, EDb, ADf, ADd, ADb, SDf, SDd, SDb;
			float Ues, Uet;
			eArmy->returnD(EDf, EDd, EDb);
			aArmy->returnD(ADf, ADd, ADb);
			countUML(Ues, Uet);

			// Battle result (in earth army's (our) point of view)
			outputFile << "\nBattle Result: " << result << endl << endl;

			// Earth Army Statistics
			outputFile << "Earth Army: \n";

			outputFile << "\tTotal number of units:\n\t";
			outputFile << "\tES: " << getLength(earthSoldier) + es + Ues;
			outputFile << "\tET: " << getLength(earthTank) + et + Uet;
			outputFile << "\tEG: " << getLength(earthGunnery) + eg;
			outputFile << "\tEH: " << getLength(earthHeal) + eh << endl;

			outputFile << "\tUnits Destruction %: \n\t";
			outputFile << "\tES: " << setprecision(4) << ((getLength(earthSoldier) + es + Ues != 0) ? float(es + Ues) / (getLength(earthSoldier) + es + Ues) * 100 : 0) << "%";
			outputFile << "\tET: " << setprecision(4) << ((getLength(earthTank) + et + Uet != 0) ? float(et + Uet) / (getLength(earthTank) + et + Uet) * 100 : 0) << "%";
			outputFile << "\tEG: " << setprecision(4) << ((getLength(earthGunnery) + eg != 0) ? float(eg) / (getLength(earthGunnery) + eg) * 100 : 0) << "%";
			outputFile << "\tEH: " << setprecision(4) << ((getLength(earthHeal) + eh != 0) ? float(eh) / (getLength(earthHeal) + eh) * 100 : 0) << "%\n";

			outputFile << "\tUnits Relative Destruction %: \n\t\t";
			outputFile << setprecision(4) << ((totalEarthUnits != 0) ? (totalDestructedEarthUnits + Uet + Ues) / totalEarthUnits * 100.0 : 0) << "%\n";

			outputFile << "\tAverage values of: \n\t";
			outputFile << "\tDf: " << ((totalDestructedEarthUnits != 0) ? EDf / totalDestructedEarthUnits : 0);
			outputFile << "\tDd: " << ((totalDestructedEarthUnits != 0) ? EDd / totalDestructedEarthUnits : 0);
			outputFile << "\tDb: " << ((totalDestructedEarthUnits != 0) ? EDb / totalDestructedEarthUnits : 0) << "\n\t";

			outputFile << "\tDf/Db%: " << setprecision(4) << ((EDb != 0) ? EDf / EDb * 100 : 0) << "%";
			outputFile << "\tDd/Db%: " << setprecision(4) << ((EDb != 0) ? EDd / EDb * 100 : 0) << "%\n";

			outputFile << "\tHealed Percentage: " << setprecision(4) << ((totalEarthUnits != 0) ? float(eArmy->getHealed()) / totalEarthUnits * 100 : 0) << "%\n";
			outputFile << "\tInfected Percentage: " << setprecision(4) << ((getLength(earthSoldier) + es + Ues != 0) ? float(getEarthArmy()->getTotalInfected()) / (getLength(earthSoldier) + es + Ues) * 100 : 0) << "%\n\n";


			// Alien Army Statistics
			outputFile << "Alien Army: \n";

			outputFile << "\tTotal number of units:\n";
			outputFile << "\t\tAS: " << getLength(alienSoldier) + as;
			outputFile << "\tAM: " << getLength(alienMonster) + am;
			outputFile << "\tAD: " << getLength(alienDrone) + ad << endl;

			outputFile << "\tUnits Destruction %: \n\t";
			outputFile << "\tAS: " << setprecision(4) << ((getLength(alienSoldier) + as != 0) ? float(as) / (getLength(alienSoldier) + as) * 100 : 0) << "%";
			outputFile << "\tAM: " << setprecision(4) << ((getLength(alienMonster) + am != 0) ? float(am) / (getLength(alienMonster) + am) * 100 : 0) << "%";
			outputFile << "\tAD: " << setprecision(4) << ((getLength(alienDrone) + ad != 0) ? float(ad) / (getLength(alienDrone) + ad) * 100 : 0) << "%\n";

			outputFile << "\tUnits Relative Destruction %: \n\t\t";
			outputFile << setprecision(4) << ((totalAlienUnits != 0) ? totalDestructedAlienUnits / totalAlienUnits * 100.0 : 0) << "%\n";

			outputFile << "\tAverage values of: \n\t";
			outputFile << "\tDf: " << ((totalDestructedAlienUnits != 0) ? ADf / totalDestructedAlienUnits : 0);
			outputFile << "\tDd: " << ((totalDestructedAlienUnits != 0) ? ADd / totalDestructedAlienUnits : 0);
			outputFile << "\tDb: " << ((totalDestructedAlienUnits != 0) ? ADb / totalDestructedAlienUnits : 0) << "\n\t";

			outputFile << "\tDf/Db%: " << setprecision(4) << ((ADb != 0) ? ADf / ADb * 100 : 0) << "%";
			outputFile << "\tDd/Db%: " << setprecision(4) << ((ADb != 0) ? ADd / ADb * 100 : 0) << "%\n\n";

		}
		outputFile.close();
	}
}

void Game::printAll()
{

	cout << getColor("blinking") << "\nCurrent Timestep " << timestep << getColor("white") << "\n";

	if (Unit::getTotalUnits(earthArmy) >= 999)
		cout << "Earth units limit exceeded\n";
	if (Unit::getTotalUnits(alienArmy) >= 999)
		cout << "Alien units limit exceeded\n";

	cout << "\n============== Earth Army Alive Units ======================\n";
	eArmy->print();

	cout << "\n============== Ally Army Alive Units =======================\n";
	sArmy->print();

	cout << "\n============== Alien Army Alive Units ======================\n";
	aArmy->print();

	cout << "\n============== Fighting at current step ====================\n";
	cout << log;
	log.clear();

	cout << "\n==============" << getColor("red") << " Killed/Destructed Units " << getColor("white") << "=====================\n";
	cout << killedList.length() << " units [";
	killedList.printAll();
	cout << "]\n";

	cout << "\n============== Units Maintenance List ======================\n";
	cout << UML.length() << " units [";
	UML.printAll();
	cout << "]\n\n";

	system("pause");
	cout << endl;
}

EarthArmy* Game::getEarthArmy() const
{
	return eArmy;
}

AlienArmy* Game::getAlienArmy() const
{
	return aArmy;
}

AllyArmy* Game::getAllyArmy() const
{
	return sArmy;
}

int Game::getLength(unitType s) const
{
	if (s < alienSoldier)
		return eArmy->getLength(s);
	else if (s < alienArmy)
		return aArmy->getLength(s);
	return sArmy->getLength(s);
}

bool Game::isEmpty(unitType s) const
{
	if (s < alienSoldier)
		return eArmy->isEmpty(s);
	else if (s < alienArmy)
		return aArmy->isEmpty(s);
	return sArmy->isEmpty(s);
}

bool Game::getUnit(unitType s, Unit*& unit) const
{
	if (s < alienSoldier)
		return eArmy->getUnit(s, unit);
	else if (s < alienArmy)
		return aArmy->getUnit(s, unit);
	return sArmy->getUnit(s, unit);
}

bool Game::addUnit(Unit*& unit)
{
	if (unit->getType() < alienSoldier)
		return eArmy->addUnit(unit);
	else if (unit->getType() < alienArmy)
		return aArmy->addUnit(unit);
	return sArmy->addUnit(unit);
}

bool Game::isOver(bool fought)
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
		else if (!fought)
		{
			result = "Tie";
			updateFile();
			return true;
		}
	}

	return false;
}

bool Game::kill(Unit*& unit)
{
	switch (unit->getType())
	{
	case earthSoldier:
		++es;
		break;
	case earthTank:
		++et;
		break;
	case earthGunnery:
		++eg;
		break;
	case alienSoldier:
		++as;
		break;
	case alienMonster:
		++am;
		break;
	case alienDrone:
		++ad;
		break;
	case earthHeal:
		++eh;
		break;
	case saverUnit:
		++su;
		break;
	}
	if (unit->getType() < alienSoldier)
		eArmy->updateD(unit);
	else if(unit->getType() < alienArmy)
		aArmy->updateD(unit);

	updateFile(unit);
	if (unit->isInfected())
		eArmy->decInfected();

	return killedList.enqueue(unit);
}

bool Game::toUML(Unit*& unit)
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

bool Game::toLog(Unit* a, Unit* b, string s)
{
	if (a == b && a != nullptr)
		log += "ES " + getColor("blue") +to_string(a->getID()) + getColor("white") + " got infected\n";
	else
		if (a && b)
		{
			switch (a->getType())
			{
			case earthSoldier:
				log = log + "ES " + a + " shots [";
				break;
			case earthTank:
				log = log + "ET " + a + " shots [";
				break;
			case earthGunnery:
				log = log + "EG " + a + " shots [";
				break;
			case alienSoldier:
				log = log + "AS " + a + " shots [";
				break;
			case alienMonster:
				log = log + "AM " + a + " attacks [";
				break;
			case alienDrone:
				log = log + "AD " + a + " shots [";
				break;
			case earthHeal:
				log = log + "EH " + a + " heals [";
				break;
			case saverUnit:
				log = log + "SU " + a + " shots [";
				break;
			}
			log = log + b;
		}
		else if (a)
		{
			log += "\033[0m, ";
			log = log + a;
		}
		else if (!s.length())
			log += "\033[0m]\n";
	log += s;
	return true;
}

bool Game::peekUnit(unitType s, Unit*& unit) const
{
	if (s < alienSoldier)
		return eArmy->peekUnit(s, unit);
	return aArmy->peekUnit(s, unit);
}

int Game::getTimestep() const
{
	return timestep;
}

void Game::war(int c)		// Main loop (As desired: Generate, Fight, Print)
{
	bool over = false;
	bool fought = false;
	while (!over)
	{
		random->addUnits();		// Adding units to all armies

		fought = fight();		// Calling both armies to fight one another
		
		if (c == 2)				// Printing the output screen if in interactive mode
			printAll();

		over = isOver(fought);	// Check the winning status
		update();

		++timestep;
	}
}

bool Game::fight()
{
	bool e, a;
	e = eArmy->fight();
	sArmy->fight();		// No need to get the fighting status of saver units
	a = aArmy->fight();

	return e || a;
}

bool Game::getUML(Unit*& unit)
{
	int p;
	if (UML.dequeue(unit, p))
		return true;
	return false;
}

void Game::countUML(float& es, float& et)	// Destructs the UML and counts the number of ET & EG
{
	float Ues = 0 , Uet = 0;
	Unit* unit = nullptr;
	int n;
	while (UML.dequeue(unit, n))
	{
		if (unit->getType() == earthSoldier)
			++Ues;
		else
			++Uet;
		delete unit;
		unit = nullptr;
	}
	es = Ues;
	et = Uet;
}

bool Game::canInfect() const
{
	return random->canInfect();
}

bool Game::canSpread() const
{
	return random->canSpread();
}

bool Game::spreadInfection()
{
	bool succeded = false;
	for (int i = 0; i < eArmy->getinfCount(); ++i)
	{
		if (canSpread())
		{
			Unit* toInfect = nullptr;
			if (getRandomES(toInfect))
			{
				if (toInfect->getInfected())
				{
					toLog(toInfect, toInfect);
					succeded = true;
				}
			}
		}
	}

	return succeded;
}

void Game::allyArmyNotNeeded()
{
	if (!getEarthArmy()->getinfCount())
	{
		Unit* tempUnit = nullptr;
		while (getUnit(saverUnit, tempUnit))
		{
			delete tempUnit;
			tempUnit = nullptr;
		}
	}
}

bool Game::getRandomES(Unit*& ES) const
{
	if (eArmy->getLength(earthSoldier))
	{
		ES = nullptr;
		int randomIndex = random->generateIndex(eArmy->getLength(earthSoldier));
		return eArmy->getRandomES(ES, randomIndex);
	}

	return false;
}
void Game::update()
{
	spreadInfection();
	allyArmyNotNeeded();
}

string Game::getColor(string color)		// To set the output display colors
{
	if (playTheme == 2) 
	{
		if (color == "blue")
			return "\033[1;94m"; // Blue
		if (color == "green")
			return "\033[1;32m"; // Green
		if (color == "yellow")
			return "\033[33m"; // Yellow
		if (color == "red")
			return "\033[0;31m"; // Red
		if (color == "white")
			return "\033[1;0m"; // White
		if (color == "blinking")
			return "\033[1;5m"; // Blinking
	}
	return ""; // Default: empty string
}


Game::~Game()		// UML is destructed in countUML() function
{
	delete eArmy;
	delete aArmy;
	delete sArmy;
	delete random;
	Unit* temp;
	while (killedList.dequeue(temp))
	{
		delete temp;
		temp = nullptr;
	}
}
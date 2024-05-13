#include "Game.h"
Game::Game() : timestep(1), as(0), am(0), ad(0), es(0), eg(0), et(0), eh(0),Ues(0), Uet(0), totalEDf(0), totalEDd(0), totalEDb(0),
				totalADf(0), totalADd(0), totalADb(0)
{
	eArmy = new EarthArmy;
	aArmy = new AlienArmy;
	sArmy = new AlliedArmy;
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
	cout << "Enter the input file name: ";
	cin >> inputFileName;
	if (inputFileName.find(".txt") == string::npos)
		inputFileName += ".txt";
	int N, NS, es, et, eg, eh, as, am, ad, probability, inf, inft, epl, eph,
		ehl, ehh, ecl, ech, apl, aph, ahl, ahh, acl, ach, spl, sph, shl, shh, scl, sch;		// Variables to store values from the input file

	fstream inputFile;
	inputFile.open(inputFileName, ios::in);
	while (!inputFile.is_open())
	{
		cout << "File doesn't exist.\nEnter the input file name: ";
		cin >> inputFileName;
		if (inputFileName.find(".txt") == string::npos)
			inputFileName += ".txt";
		inputFile.open(inputFileName, ios::in);
	}

	if (inputFile.is_open())
	{
		inputFile >> N >> NS >> es >> et >> eg >> eh >> as >> am >> ad >> probability >> inf >> inft;									// Reading first 10 digits
		inputFile >> epl >> eph >> ehl >> ehh >> ecl >> ech >> apl >> aph >> ahl >> ahh >> acl >> ach ;
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

void Game::updateFile(Units* unit)
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
			countUML();
			float totalEarthUnits = Units::getTotalUnits(earthArmy);
			float totalDestructedEarthUnits = es + et + eg + eh;
			float totalAlienUnits = Units::getTotalUnits(alienArmy);
			float totalDestructedAlienUnits = as + ad + am;

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
			outputFile << "\tET: " << setprecision(4) << ((getLength(earthTank) + et + Uet !=0 ) ? float(et + Uet) / (getLength(earthTank) + et + Uet) * 100  : 0)<< "%";
			outputFile << "\tEG: " << setprecision(4) << ((getLength(earthGunnery) + eg != 0) ? float(eg) / (getLength(earthGunnery) + eg) * 100 : 0)  << "%";
			outputFile << "\tEH: " << setprecision(4) << ((getLength(earthHeal) + eh != 0) ? float(eh) / (getLength(earthHeal) + eh) * 100 : 0) << "%\n";

			outputFile << "\tUnits Relative Destruction %: \n\t\t";
			outputFile << setprecision(4) << ((totalEarthUnits != 0) ? (totalDestructedEarthUnits + Uet + Ues) / totalEarthUnits * 100.0 : 0)<< "%\n";

			outputFile << "\tAverage values of: \n\t";
			outputFile << "\tDf: " << setprecision(2) << ((totalDestructedEarthUnits != 0) ? float(totalEDf) / totalDestructedEarthUnits : 0);
			outputFile << "\tDd: " << setprecision(2) << ((totalDestructedEarthUnits != 0) ? float(totalEDd) / totalDestructedEarthUnits : 0);
			outputFile << "\tDb: " << setprecision(2) << ((totalDestructedEarthUnits != 0) ? float(totalEDb) / totalDestructedEarthUnits : 0) << "\n\t";

			outputFile << "\tDf/Db%: " << setprecision(4) << ((totalEDb != 0) ? float(totalEDf) / totalEDb * 100 : 0) << "%";
			outputFile << "\tDd/Db%: " << setprecision(4) << ((totalEDb != 0) ? float(totalEDd) / totalEDb * 100 : 0) << "%\n";

			outputFile << "\tHealed Percentage: " << setprecision(4) << ((totalEarthUnits !=0) ? float(healed) / totalEarthUnits  * 100 : 0) << "%\n\n";

      
			// Alien Army Statistics
			outputFile << "Alien Army: \n";

			outputFile << "\tTotal number of units:\n";
			outputFile << "\t\tAS: " << getLength(alienSoldier) + as;
			outputFile << "\tAM: " << getLength(alienMonster) + am;
			outputFile << "\tAD: " << getLength(alienDrone) + ad << endl;

			outputFile << "\tUnits Destruction %: \n";
			outputFile << "\t\tAS: " << setprecision(3) << ((getLength(alienSoldier) + as != 0) ? float(as) / (getLength(alienSoldier) + as) * 100 : 0) << "%";
			outputFile << "\tAM: " << setprecision(3) << ((getLength(alienMonster) + am != 0) ? float(am) / (getLength(alienMonster) + am) * 100 : 0) << "%";
			outputFile << "\tAD: " << setprecision(3) << ((getLength(alienDrone) + ad != 0) ? float(ad) / (getLength(alienDrone) + ad) * 100 : 0) << "%\n";

			outputFile << "\tUnits Relative Destruction %: \n\t\t";
			outputFile << setprecision(4) << ((totalAlienUnits != 0) ? totalDestructedAlienUnits / totalAlienUnits * 100.0 : 0) << "%\n";

			outputFile << "\tAverage values of: \n\t";
			outputFile << "\tDf: " << setprecision(2) << ((totalDestructedAlienUnits != 0)? float(totalADf) / totalDestructedAlienUnits : 0);
			outputFile << "\tDd: " << setprecision(2) << ((totalDestructedAlienUnits != 0) ? float(totalADd) / totalDestructedAlienUnits : 0);
			outputFile << "\tDb: " << setprecision(2) << ((totalDestructedAlienUnits != 0) ? float(totalADb) / totalDestructedAlienUnits : 0) << "\n\t";

			outputFile << "\tDf/Db%: " << setprecision(4) << ((totalADb != 0) ? float(totalADf) / totalADb * 100 : 0) << "%";
			outputFile << "\tDd/Db%: " << setprecision(4) << ((totalADb != 0) ? float(totalADd) / totalADb * 100 : 0) << "%\n\n";
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

	cout << "\n\033[44m============== Earth Army Alive Units ============\033[40m\n";
	eArmy->print();
	cout << endl;

	if(!sArmy->isEmpty(alliedArmy))
	{
		cout << "\n\033[104m============== Allied Army Alive Units ============\033[40m\n";
		sArmy->print();
		cout << endl;
	}

	cout << "\033[42m============== Alien Army Alive Units ==============\033[40m\n";
	aArmy->print();
	cout << endl;

	cout << "\033[45m============== Units fighting at current step =============\033[40m\n";
	cout << log;
	log.clear();
	cout << endl;

	cout << "\033[41m============== Killed/Destructed Units =============\033[40m\n";
	cout << killedList.length() << " units [";
	killedList.printAll();
	cout << "]\n\n";

	cout << "\033[43m============== UML =============\033[40m\n";
	cout << UML.length() << " units [";
	UML.printAll();
	cout << "]\n\n";

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
AlliedArmy* Game::getAlliedArmy()
{
	return sArmy;
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

bool Game::isOver(bool a, bool b , bool c)
{
	if (timestep >= 40)
	{
		if (eArmy->isEmpty(earthArmy) && aArmy->isEmpty(alienArmy) && sArmy->isEmpty(alliedArmy) || !(a || b))
		{
			result = "Tie";
			updateFile();
			return true;
		}
		else if (eArmy->isEmpty(earthArmy))
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
	}
	return false;
}

bool Game::kill(Units*& unit)
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
	}
	updateFile(unit);
	if(unit->isInfected())
	unit->getCured();
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

bool Game::toLog(Units* a, Units* b)
{
	if (a && b)
	{
		switch (a->getType())
		{
		case earthSoldier:
			log += "ES ";
			if(b->isInfected()) 
			{
				log += "\033[1;32m$\033[1;34m";
				log +=  to_string(a->getID()) + "\033[1;37m infected [";
			}
			else
			{
				log += "\033[1;34m" + to_string(a->getID());
				log += "\033[1;37m shots [";
			}

			break;
		case earthTank:
			log += "ET \033[1;34m" + to_string(a->getID()) + "\033[1;37m shots [";
			break;
		case earthGunnery:
			log += "EG \033[1;34m" + to_string(a->getID()) + "\033[1;37m shots [";
			break;
		case alienSoldier:
			log += "AS \033[1;32m" + to_string(a->getID()) + "\033[1;37m shots [";
			break;
		case alienMonster:
			log += "AM \033[1;32m" + to_string(a->getID()) + "\033[1;37m attacks [";
			break;
		case alienDrone:
			log += "AD \033[1;32m" + to_string(a->getID()) + "\033[1;37m shots [";
			break;
		case earthHeal:
			log += "EH \033[1;34m" + to_string(a->getID()) + "\033[1;37m heals [";
			break;
		case saverUnit:
			log += "SU \033[1;33m" + to_string(a->getID()) + "\033[1;37m shots [";
			break;
		}
		switch (b->getType())
		{
		case earthSoldier:
			log += "\033[1;34m" + to_string(b->getID());
			break;
		case earthTank:
			log += "\033[1;34m" + to_string(b->getID());
			break;
		case earthGunnery:
			log += "\033[1;34m" + to_string(b->getID());
			break;
		case alienSoldier:
			log += "\033[1;32m" + to_string(b->getID());
			break;
		case alienMonster:
			log += "\033[1;32m" + to_string(b->getID());
			break;
		case alienDrone:
			log += "\033[1;32m" + to_string(b->getID());
			break;
		case earthHeal:
			log += "\033[1;34m" + to_string(b->getID());
			break;
		case saverUnit:
			log += "\033[1;33m" + to_string(b->getID());
			break;
		}
	}
	else if (a)
	{
		switch (a->getType())
		{
		case earthSoldier:
			log += "\033[1;37m, \033[1;34m" + to_string(a->getID());
			break;
		case earthTank:
			log += "\033[1;37m, \033[1;34m" + to_string(a->getID());
			break;
		case earthGunnery:
			log += "\033[1;37m, \033[1;34m" + to_string(a->getID());
			break;
		case alienSoldier:
			log += "\033[1;37m, \033[1;32m" + to_string(a->getID());
			break;
		case alienMonster:
			log += "\033[1;37m, \033[1;32m" + to_string(a->getID());
			break;
		case alienDrone:
			log += "\033[1;37m, \033[1;32m" + to_string(a->getID());
			break;
		case earthHeal:
			log += "\033[1;37m, \033[1;34m" + to_string(a->getID());
			break;
		case saverUnit:
			log += "\033[1;37m, \033[1;34m" + to_string(a->getID());
			break;
		}
	}
	else
		log += "\033[1;37m]\n";

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

		bool e = eArmy->fight();						// Calling both armies to fight one another
		bool s = sArmy->fight();						//Useless bool
		bool a = aArmy->fight();

		if(c==2)
			printAll();			// Printing the output screen

		over = isOver(e, a, s);

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

void Game::updateED(Units* unit)
{
	totalEDd += unit->getDd();
	totalEDb += unit->getDb();
	totalEDf += unit->getDf();
}

void Game::updateAD(Units* unit)
{
	totalADd += unit->getDd();
	totalADb += unit->getDb();
	totalADf += unit->getDf();
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

bool Game::canInfect()
{
	return random->canInfect();
}

bool Game::canSpread()
{
	return random->canSpread();
}

bool Game::getRandomES(Units*& ES)
{
	ES = nullptr;
	int randomIndex = random->generateIndex(eArmy->getLength(earthSoldier));
	return eArmy->getRandomES(ES, randomIndex);
}

Game::~Game()
{
	delete eArmy;
	delete aArmy;
	delete sArmy;
	delete random;
	while (!killedList.isEmpty())
	{
		Units* temp;
		killedList.dequeue(temp);
		delete temp;
	}
}
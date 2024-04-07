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

void Game::simulate()
{
	LinkedQueue<Units*> tempList;		// To store units temporarily
	Units* tempUnit = nullptr;			// To point to a unit temporarily
	for (int i = 0; i < 50; ++i)			// 50 timesteps for phase 1.2 test code
	{
		addArmy();
		int x = random->generateNum();
		cout << "Current Timestep " << timestep++ << "\n";

		if (x < 10)
		{
			if (!eArmy->isEmpty('S'))		// if no soldiers found do nothing
			{
				eArmy->removeSoldier(tempUnit);
				eArmy->AddUnit(tempUnit);
			}
		}
		else if (x < 20)
		{
			if (!eArmy->isEmpty('T'))		// if no tanks found do nothing
			{
				eArmy->removeTank(tempUnit);
				killedList.enqueue(tempUnit);
			}
		}
		else if (x < 30)
		{
			if (!eArmy->isEmpty('G'))		// if no Gunneries found do nothing
			{
				eArmy->removeGunnery(tempUnit);
				tempUnit->GetAttacked(tempUnit->getCurHealth() / 2);
				eArmy->AddUnit(tempUnit);
			}
		}
		else if (x < 40)
		{
			if (aArmy->length('S') >= 5)		// if soldiers are less than 5 do nothing
			{
				for (int i = 0; i < 5; ++i)
				{
					aArmy->removeSoldier(tempUnit);
					tempUnit->GetAttacked(tempUnit->getCurHealth() / 3);
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
			if (aArmy->length('M') >= 5)		// if monsters are less than 5 do nothing
			{
				for (int i = 0; i < 5; ++i)
				{
					aArmy->removeMonster(random->getMonsterIndex(aArmy->length('M')), tempUnit);
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
			if (aArmy->length('D') >= 6)
			{
				for (int i = 0; i < 6; ++i)
				{
					aArmy->removeDrone(tempUnit);
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

void Game::addArmy() 
{
	Units* newBorn;
	int N;
	if (random->probability(N)) {
		for (int i = 0; i < N; i++) {
			newBorn = random->generateAlien(timestep);
			aArmy->addUnit(newBorn);
		}
	}
	if (random->probability(N)) {
		for (int i = 0; i < N; i++) {
			newBorn = random->generateEarth(timestep);
			eArmy->AddUnit(newBorn);
		}
	}
}
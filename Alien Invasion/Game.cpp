#include "Game.h"

Game::Game(): timestep(1), N(0), isOver(false){
	eArmy = new EarthArmy;
	aArmy = new AlienArmy;
	setRandom();
}

void Game::setRandom() {
	int es, et, eg, as, am, ad, probability, epl, eph,
		ehl, ehh, ecl, ech, apl, aph, ahl, ahh, acl, ac;		// Variables to store values from the input file

	fstream inputFile;
	string fileName = "input.txt";
	inputFile.open(fileName, ios::in);
	if (inputFile.is_open()) {
		inputFile >> N >> es >> et >> eg >> as >> am >> ad >> probability;									// Reading first 8 digits
		inputFile >> epl >> eph >> ehl >> ehh >> ecl >> ech >> apl >> aph >> ahl >> ahh >> acl >> ac;

		random = new randGen(N, es, et, eg, as, am, ad, probability, epl, abs(eph),							// Take absolute to any high-value 
			ehl, abs(ehh), ecl, abs(ech), apl, abs(aph), ahl, abs(ahh), acl, abs(ac));						//	to handle the range dash '-'
	}
	else {
		throw std::ios_base::failure("Failed to open file");												// File didn't open properly
	} 
}

void Game::printAll() {
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
	for (int i = 0; i < 50; ++i)			// 50 timesteps for phase 1.2 test code
	{
		addArmy();
		int x = random->generateNum();
		cout << "Current Timestep " << timestep++ << "\n";
		LinkedQueue<Units*> tempList;		// To store units temporarily
		Units* tempUnit = nullptr;			// To point to a unit temporarily

		if (x < 10)
		{
			if (!eArmy->IsEmptyES())
			{
				tempUnit = eArmy->removeSoldier();
				eArmy->AddUnit(tempUnit);
			}
		}
		else if (x < 20)
		{
			if (!eArmy->IsEmptyET())
			{
				tempUnit = eArmy->removeTank();
				killedList.enqueue(tempUnit);
			}
		}
		else if (x < 30)
		{
			if (!eArmy->IsEmptyEG())
			{
				tempUnit = eArmy->removeGunnery();
				tempUnit->GetAttacked(tempUnit->getCurHealth() / 2);
				eArmy->AddUnit(tempUnit);
			}
		}
		else if (x < 40)
		{
			if (aArmy->lengthAS() >= 5)
			{
				for (int i = 0; i < 5; ++i)
				{
					tempUnit = aArmy->removeSoldier();
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
			if (aArmy->lengthAM() >= 5)
			{
				for (int i = 0; i < 5; ++i)
				{
					tempUnit = aArmy->removeMonster(random->getMonsterIndex(aArmy->lengthAM()));
					tempList.enqueue(tempUnit);
				}
				for (int i = 0; i < 5; ++i)
				{
					tempList.dequeue(tempUnit);
					aArmy->addUnit(tempUnit);
				}
			}
		}
		else if (x < 60)
		{
			if (aArmy->lengthAD() >= 6)
			{
				for (int i = 0; i < 6; ++i)
				{
					tempUnit = aArmy->removeDrone();
					tempList.enqueue(tempUnit);
				}
				for (int i = 0; i < 6; ++i)
				{
					tempList.dequeue(tempUnit);
					killedList.enqueue(tempUnit);
				}
			}
		}
		printAll();
		system("pause");
		cout << endl;
	}
}

void Game::addArmy() {
	Units* newBorn;
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
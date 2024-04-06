#include "Game.h"

Game::Game(){
	timestep = 1;
	N = 0;
	isOver = false;
	eArmy = new EarthArmy;
	aArmy = new AlienArmy;
	setRandom();
}

void Game::setRandom() {
	int es, et, eg, as, am, ad, probability, epl, eph,
		ehl, ehh, ecl, ech, apl, aph, ahl, ahh, acl, ac;

	fstream inputFile;
	string fileName = "input.txt";
	inputFile.open(fileName, ios::in);
	if (inputFile.is_open()) {
		inputFile >> N >> es >> et >> eg >> as >> am >> ad >> probability;									//Reading first 8 digits
		inputFile >> epl >> eph >> ehl >> ehh >> ecl >> ech >> apl >> aph >> ahl >> ahh >> acl >> ac;		// Take absolute to any high value

		random = new randGen(N, es, et, eg, as, am, ad, probability, epl, abs(eph),
			ehl, abs(ehh), ecl, abs(ech), apl, abs(aph), ahl, abs(ahh), acl, abs(ac));
	}
	else {
		throw std::ios_base::failure("Failed to open file");
	}
}

void Game::printAll() {
	cout << "============== Earth Army Alive Units =============\n";
	eArmy->print();
	cout << endl;
	cout << "============== Alien Army Alive Units =============\n";
	aArmy->print();
	cout << "============== Killed List =============\n";
	killedList.printAll();
}

void Game::simulate()
{
	for (int i = 0; i < 50; ++i)
	{
		addArmy();

		int x = random->generateNum();

		if (x < 10)
		{
			Units* tempES = nullptr;
			tempES = eArmy->removeSoldier();
			if (tempES)
			{
				eArmy->AddUnit(tempES);
				cout << "Removed ES " << tempES << " from it's list and returned it again.\n";
			}
			else
				cout << "no ES found";
		}
		else if (x < 20)
		{
			Units* tempET = nullptr;
			tempET = eArmy->removeTank();
			if (tempET)
			{
				killedList.enqueue(tempET);
				cout << "Moved ET " << tempET << " to killed list.\n";
			}
			else
				cout << "no ET found";
		}
		else if (x < 30)
		{
			Units* tempEG = nullptr;
			tempEG = eArmy->removeGunnery();
			if (tempEG)
			{
				tempEG->GetAttacked(tempEG->getCurHealth() / 2);
				eArmy->AddUnit(tempEG);
				cout << "Decremented Gunnery " << tempEG << "'s health to it's half and returned it to it's list list.\n";
			}
			else
				cout << "no EG found";
		}
		else if (x < 40)
		{
			LinkedQueue<Units*> tempList;
			Units* tempAS;
			for (int i = 0; i < 5; ++i)
			{
				tempAS = aArmy->removeSoldier();
				if (tempAS)
				{
					tempAS->GetAttacked(tempAS->getCurHealth() / 3);
					tempList.enqueue(tempAS);
				}
				else
				{
					cout << "no AS found";
					break;
				}
			}
			if (tempAS)
			{
				cout << "Picked 5 AS, Decremented their health by it's third and inserted them again.\nAS IDs: [ ";
				for (int i = 0; i < 5; ++i)
				{
					tempList.dequeue(tempAS);
					cout << tempAS << " ";
					aArmy->addUnit(tempAS);
				}
				cout << "].";
			}
		}
		else if (x < 50)
		{
			LinkedQueue<Units*> tempList;
			Units* tempAM;
			int m = random->generateNum();
			for (int i = 0; i < 5; ++i)
			{
				tempAM = aArmy->removeMonster(m);
				if (tempAM)
					tempList.enqueue(tempAM);
				else
				{
					cout << "no AM found";
					break;
				}
			}
			if (tempAM)
			{
				cout << "Picked 5 AM and inserted them again.\nAM IDs: [ ";
				for (int i = 0; i < 5; ++i)
				{
					tempList.dequeue(tempAM);
					cout << tempAM << " ";
					aArmy->addUnit(tempAM);
				}
				cout << "].";
			}
		}
		else if (x < 60)
		{
			Units* tempAD;
			tempAD = aArmy->removeDrone();
			if (tempAD)
			{
				cout << "Moved 6 ADs to killed list.\nAD IDs: [ ";
				for (int i = 0; i < 6; ++i)
				{
					tempAD = aArmy->removeDrone();
					if (tempAD)
					{
						cout << tempAD << " ";
						killedList.enqueue(tempAD);
					}
					else
					{
						cout << "no AD found";
						break;
					}
				}
				cout << "].";
			}
			else
				cout << "no AD found";
		}
		else 
			cout << "prob > 60\n";

		cout << "Current Timestep " << timestep++ << endl;	

		/*do
		{
			cout << '\n' << "Press Enter to continue...";
		} while (cin.get() != '\n');*/

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
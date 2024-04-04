#include "Game.h"

Game::Game(){
	timestep = 0;
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
	eArmy->print();
	cout << endl;
	aArmy->print();
}

void Game::addArmy() {
	Units* newBorn;
	int i = 0;
	while (i<2) { //!isOver()
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
			timestep++;
			i++;
		}
}
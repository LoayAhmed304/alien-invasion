#pragma once

class randGen
{
private:
	int N, ES, ET, EG, AS, AM, AD, prob,
		earthPowerLow, earthPowerHigh,
		earthHealthLow, earthHealthHigh,
		earthCapLow, earthCapHigh,
		alienPowerLow, alienPowerHigh,
		alienHealthLow, alienHealthHigh,
		alienCapLow, alienCapHigh;
public:
	randGen(int n, int es, int et, int eg,
		int as, int am, int ad, int probability,
		int epl, int eph, int ehl, int ehh, int ecl, int ech,
		int apl, int aph, int ahl, int ahh, int acl, int ach);
	bool probability();
	unit* generateEarth(int timeStep);
	unit* generateAlien(int timeStep);
	~randGen();
};
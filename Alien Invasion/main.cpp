#include <iostream>
#include "Units/Units.h"
#include "Units/EarthArmy.h"

using namespace std;
int main() 
{

    Units* x1 = new Earth_Soldier;
    Units* x2 = new Earth_Soldier;
    Units* x3 = new Earth_Soldier;
    Units* x4 = new Earth_Soldier;

    EarthArmy* EA = new EarthArmy;
    EA->AddUnit(x1);
    EA->AddUnit(x2);
    EA->AddUnit(x3);
    EA->AddUnit(x4);

    EA->print();
    return 0;
}
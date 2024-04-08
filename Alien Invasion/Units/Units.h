#ifndef UNITS_H
#define UNITS_H

#include <iostream>
using namespace std;
class Game;

enum unitType
{
    earth,
    earthSoldier,
    earthTank,
    earthGunnery,
    alien,
    alienSoldier,
    alienMonster,
    alienDrone
};

class Units 
{
private:
    unitType type;
    int Tj, Ta, Td, Df, Dd, UAP, health, power, attack_cap, cur_health;
    Game* game;
protected:
    int id;
    static int eID;
    static int aID;
public:
    Units(unitType type, int power, int health, int atk_cap, int timestep);
    virtual bool Attack() = 0;
    virtual bool GetAttacked(int dmg);
    virtual bool IsDead() = 0;
    virtual unitType getType() const;
    virtual int getHealth() const;
    virtual int getCurHealth() const;
    virtual int getPower() const;
    virtual int getAttackCap() const;
    friend std::ostream& operator<<(std::ostream& os, const Units* obj);
};
#endif
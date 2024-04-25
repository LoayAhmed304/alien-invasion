#ifndef UNITS_H
#define UNITS_H

#include <iostream>
using namespace std;
class Game;

enum unitType
{
    earthSoldier,
    earthTank,
    earthGunnery,
    earthHeal,
    alienSoldier,
    alienMonster,
    alienDrone,
    alienArmy,
    earthArmy
};

class Units
{
private:
    unitType type;
    int Tj, Ta, Td, Df, Dd, Db, UAP, power, attack_cap, cur_health, TimeUML;
    double health;
    bool InsideUML;
protected:
    int id;
    static int eID;
    static int aID;
    Game* game;
public:
    Units(unitType type, int power, int health, int atk_cap, Game* g);
    virtual bool attack() = 0;
    virtual bool getAttacked(double dmg);
    virtual bool isDead();
    virtual unitType getType() const;
    virtual double getHealth() const;
    virtual double getCurHealth() const;
    virtual int getPower() const;
    virtual int getAttackCap() const;
    virtual int getHealthPerc() const;
    virtual int getTa() const;
    virtual void setTa(int);
    virtual int getID();

    virtual bool checkUML() const;
    virtual int getUMLtime();
    virtual bool insideUML();
    virtual bool exitUML();
    virtual bool enterUML();


    friend std::ostream& operator<<(std::ostream& os, const Units* obj);
};
#endif
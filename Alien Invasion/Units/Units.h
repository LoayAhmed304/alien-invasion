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
    earthArmy,
    saverUnit,
    alliedArmy
};

class Units
{
private:
    unitType type;
    int Tj, Ta, Td, Df, Dd, Db, UAP, power, attack_cap, cur_health, TimeUML;
    double health;
    bool healed;
    bool infected = false;
    bool cured = false;
    int HT = 0;
protected:
    int id;
    static int eID;
    static int aID;
    static int sID;
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

    static int getTotalUnits(unitType);

    virtual int getID() const;
    virtual int getTd() const;
    virtual int getTj() const;
    virtual int getDf() const;
    virtual int getDd() const;
    virtual int getDb() const;
    virtual int getTa() const;
    virtual void setTa(int);
    virtual int getID();

    virtual bool isHealed();
    virtual void heal();

    virtual int getUMLtime();
    virtual bool exitUML();
    virtual bool enterUML();

    virtual bool isInfected() const;
    virtual bool isCured();
    virtual bool getInfected();
    virtual void removeInfected();
    virtual void getCured();

    virtual int getHT();
    virtual void setHT(int);
    virtual void incHT();

    friend std::ostream& operator<<(std::ostream& os, const Units* obj);
};
#endif
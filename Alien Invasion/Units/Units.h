#ifndef UNITS_H
#define UNITS_H

#include <iostream>
class Game;

using namespace std;

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
    allyArmy
};

class Units
{
private:
    unitType type;
    int Tj, Ta, Td, Df, Dd, Db, UAP, power, attack_cap, cur_health, timeUML;
    double health;
    bool healed;
    bool infected;
    bool cured;
    int HT;
protected:
    int id;
    static int eID;
    static int aID;
    static int sID;
    Game* game;
public:
    Units(unitType, int, int, int, Game*);
    virtual bool attack() = 0;
    virtual bool getAttacked(double);
    virtual bool isDead() const;
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
    virtual double getUAP() const;
    virtual void setUAP(double);
    virtual void setTa(int);

    virtual bool isHealed() const;
    virtual void heal();

    virtual int getUMLtime() const;
    virtual bool exitUML();
    virtual bool enterUML();

    virtual bool isInfected() const;
    virtual bool isCured() const;
    virtual bool getInfected();
    virtual void removeInfected();
    virtual void getCured();

    virtual int getHT() const;
    virtual void setHT(int);
    virtual void incHT();

    friend std::ostream& operator<<(std::ostream& os, const Units* obj);
};
#endif
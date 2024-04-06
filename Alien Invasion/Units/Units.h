#ifndef UNITS_H
#define UNITS_H

#include <iostream>
using namespace std;

class Units 
{
private:
    string type;
    int Tj,Ta,Td,Df,Dd,UAP;
    int health, power, attack_cap,cur_health;
protected:
    int id;
    static int eID;
    static int aID;
public:
    Units(string type, int power, int health, int atk_cap, int timestep);
    virtual bool Attack() = 0;
    virtual bool GetAttacked(int dmg);
    virtual bool IsDead() = 0;
    virtual string getType() const;
    virtual int getHealth() const;
    virtual int getCurHealth() const;
    virtual int getPower() const;
    virtual int getAttackCap() const;
    friend std::ostream& operator<<(std::ostream& os, const Units* obj);
};
#endif
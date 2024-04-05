#pragma once
#include <string>
#include <iostream>
using namespace std;
class Units 
{
private:
    string type;
    int Tj,Ta,Td,Df,Dd,UAP;
    int health, Power, attack_cap;
protected:
    int id;
    static int eID;
    static int aID;
public:
    Units(string, int, int, int, int);
    virtual bool Attack() = 0;
    virtual bool GetAttacked() = 0;
    virtual bool IsDead() = 0;
    friend std::ostream& operator<<(std::ostream& os, const Units* obj) 
    {
        os << " " << obj->id ;
        return os;
    }
};


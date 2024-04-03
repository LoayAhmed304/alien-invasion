#pragma once
#include <string>
using namespace std;
class Units 
{
private:
    int id;
    string type;
    int Tj,Ta,Td,Df,Dd,UAP;
    int health, Power, attack_cap;
protected:
    static int EarthId, AlienId;
public:
    Units()
    {
        id = EarthId;
        EarthId++;
    };
    virtual bool Attack() = 0;
    virtual bool GetAttacked() = 0;
    virtual bool IsDead() = 0;
    friend std::ostream& operator<<(std::ostream& os, const Units* obj) 
    {
        os << " " << obj->id << endl;
        return os;
    }
};
int Units::EarthId = 0;
int Units::AlienId = 0;


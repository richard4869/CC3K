#ifndef __PC_H__
#define __PC_H__
#include "character.h"
#include "gold.h"
#include "potion.h"

class Monster;
class Potion;

class PC : public Character {
protected:
    int boostDEF;
    int boostATT;
    int gold;
    char type;
    bool knownpotn[6];
    virtual void dead();
    PC(int x,int y,int hp,int att,int def,Game *game,char type);
public:
    bool eaten(int);
    int getgold();
    char gettype();
    void notify(std::string s);
    virtual void addHP(int j);
    int getATT();
    int getDEF();
    void addATT(int i);
    void addDEF(int i);
    void resetboost();
    virtual void getmoney(int);
    virtual void takepotion(Potion *);
    virtual void attack(Monster *);
    virtual ~PC()=0;
};

#endif

#ifndef __MONSTER_H__
#define __MONSTER_H__
#include "character.h"

class PC;

class Monster:public Character{
protected:
    char type;
    Monster(int x,int y,int hp,int att,int def,Game *game,char type);
    virtual void dead();
public:
    char gettype();
    void addHP(int j);
    virtual void attack(PC*);
	virtual ~Monster()=0;
	void notify(std::string);
	virtual void defend(int);
	virtual void dragonmove(PC * pc);
    virtual void returndragon();
};

#endif

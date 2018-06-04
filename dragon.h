#ifndef __DRAGON_H__
#define __DRAGON_H__
#include <iostream>
#include <sstream>
#include "monster.h"

class Gold;

class Dragon : public Monster {
public:
    Gold * dragonhoard;
    bool hostile;
    void returndragon();
    Dragon(int x,int y,Game* game);
    ~Dragon();
    void attack(PC*);
    void defend(int hp);
    void dragonmove(PC * pc);
    void addHP(int j);
};

#endif

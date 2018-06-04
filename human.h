#ifndef __HUMAN_H__
#define __HUMAN_H__
#include "monster.h"


class Human : public Monster {
public:
    Human(int x,int y,Game *game);
    ~Human();
};

#endif

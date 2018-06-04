#ifndef __ORC_H__
#define __ORC_H__
#include "monster.h"


class Orc : public Monster {
public:
    void attack(PC*);
    Orc(int x,int y,Game *game);
    ~Orc();
};

#endif

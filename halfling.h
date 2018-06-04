#ifndef __HALFLING_H__
#define __HALFLING_H__
#include "monster.h"


class Halfling : public Monster {
public:
    Halfling(int x,int y,Game *game);
    ~Halfling();
};

#endif

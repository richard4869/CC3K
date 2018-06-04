#ifndef __GOBLIN_H__
#define __GOBLIN_H__
#include "pc.h"


class Goblin : public PC {
public:
    Goblin(int x,int y,Game *game);
    ~Goblin();
};

#endif

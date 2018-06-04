#ifndef __VAMPIRE_H__
#define __VAMPIRE_H__
#include "pc.h"


class Vampire : public PC {
public:
    Vampire(int x,int y,Game *game);
    void addHP(int);
    void attack(Monster*);
    ~Vampire();
};

#endif

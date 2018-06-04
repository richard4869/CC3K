#ifndef __DROW_H__
#define __DROW_H__
#include "pc.h"


class Drow : public PC {
public:
    Drow(int x,int y,Game *game);
    void takepotion(Potion*);
    ~Drow();
};

#endif

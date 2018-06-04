#ifndef __TROLL_H__
#define __TROLL_H__
#include <iostream>
#include <sstream>
#include "pc.h"


class Troll : public PC {
public:
    Troll(int x,int y,Game *game);
    ~Troll();
};

#endif

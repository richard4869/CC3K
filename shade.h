#ifndef __SHADE_H__
#define __SHADE_H__
#include "pc.h"


class Shade : public PC {
public:
    Shade(int x,int y,Game *game);
    ~Shade();
};

#endif

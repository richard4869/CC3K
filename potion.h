#ifndef __POTION_H__
#define __POTION_H__
#include "item.h"


class Potion : public Item {
    int type;
public:
    Potion(int x,int y,int type);
    ~Potion();
    int gettype();
};

#endif

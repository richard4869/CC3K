#ifndef __GOLD_H__
#define __GOLD_H__
#include "item.h"

class Gold : public Item {
    int value;
public:
    bool linked;
    Gold(int x,int y,int val);
    ~Gold();
    int getvalue();
};

#endif

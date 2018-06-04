#ifndef __MERCHANT_H__
#define __MERCHANT_H__
#include "monster.h"


class Merchant : public Monster {
public:
    Merchant(int x,int y,Game *game);
    void attack(PC*);
    void defend(int hp);
    ~Merchant();
};

#endif

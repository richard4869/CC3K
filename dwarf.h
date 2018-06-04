#ifndef __DWARF_H__
#define __DWARF_H__
#include "monster.h"


class Dwarf : public Monster {
public:
    Dwarf(int x,int y, Game * game);
    ~Dwarf();
};

#endif

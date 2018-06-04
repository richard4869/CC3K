#ifndef __ELF_H__
#define __ELF_H__
#include "monster.h"


class Elf : public Monster {
public:
    Elf(int x,int y,Game *game);
    ~Elf();
    void attack(PC * pc);
};

#endif

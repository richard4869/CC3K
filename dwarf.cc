#include "monster.h"
#include "dwarf.h"
#include "pc.h"
// constructor with position, hp, attack, defense, its type and the game it in.

Dwarf::Dwarf(int x,int y,Game *game):
    Monster(x,y,100,20,30,game,'W'){}
// destructor
Dwarf::~Dwarf(){}

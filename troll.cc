#include "troll.h"
#include "monster.h"
#include "potion.h"
// constructor with position, hp, attack, defense, its type and the game it in.
Troll::Troll(int x,int y,Game *game):
    PC(x,y,120,25,15,game,'t'){}
// destructor
Troll::~Troll(){}

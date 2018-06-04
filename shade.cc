#include "shade.h"
#include "monster.h"
// constructor with position, hp, attack, defense, its type and the game it in.
Shade::Shade(int x,int y,Game *game):
    PC(x,y,125,25,25,game,'s'){}
// destructor
Shade::~Shade(){}

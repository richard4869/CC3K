#include "monster.h"
#include "halfling.h"
#include "pc.h"

// constructor with position, hp, attack, defense, its type and the game it in.

Halfling::Halfling(int x,int y,Game *game):
    Monster(x,y,110,25,20,game,'L'){}

// destructor
Halfling::~Halfling(){}

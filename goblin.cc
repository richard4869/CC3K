#include "goblin.h"
#include "monster.h"
#include "potion.h"

// constructor with position, hp, attack, defense, its type and the game it in.

Goblin::Goblin(int x,int y,Game *game):
    PC(x,y,110,15,20,game,'g'){}

// destructor
Goblin::~Goblin(){}

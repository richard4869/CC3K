#include "monster.h"
#include "human.h"
#include "pc.h"

// constructor with position, hp, attack, defense, its type and the game it in.
Human::Human(int x,int y,Game *game):
    Monster(x,y,140,20,20,game,'H'){}

// destructor
Human::~Human(){}

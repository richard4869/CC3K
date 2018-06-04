#include "drow.h"
#include "monster.h"
#include "potion.h"

// constructor with position, hp, attack, defense, its type and the game it in.

Drow::Drow(int x,int y,Game *game):
    PC(x,y,150,25,15,game,'d'){}

// virtual function of takepotion from pc.
// Having a special feature that get 1.5 times effect when take potion.
void Drow::takepotion(Potion *potn){
int t=potn->gettype();
int i=5*1.5;
int j=10*1.5;
switch (t){
    case 0:
        addHP(j);
        break;
    case 1:
        addATT(i);
        break;
    case 2:
        addDEF(i);
        break;
    case 3:
        addHP(-j);
        break;
    case 4:
        addATT(-i);
        break;
    case 5:
        addDEF(-i);
        break;
}
knownpotn[t] = true;
}

// destructor
Drow::~Drow(){}

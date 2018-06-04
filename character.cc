#include "character.h"
#include "game.h"

using namespace std;
// constructor with its position, hp, attack, defense and the game it in.
Character::Character(int x,int y,int hp, int att,int def,Game *game):
    x(x),
    y(y),
    ATT(att),
    DEF(def),
    HP(hp),
    maxHP(hp),
    game(game)
    {}
// set the position of character.
void Character::setxy(int x,int y){
	this->x = x;
	this->y = y;
}
// get the x-posn of the character.
int Character::getx(){
return x;
}
// get the y-posn of the character.
int Character::gety(){
return y;
}
// get the attack of the character.
int Character::getATT(){
return ATT;
}
// get the defense of the character.
int Character::getDEF(){
return DEF;
}
// get the hp of the character.
int Character::getHP(){
return HP;
}
// Move character to the given position.
void Character::chamove(int i,int j){
x=i;
y=j;
}
//destructor.
Character::~Character(){}

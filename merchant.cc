#include "monster.h"
#include "merchant.h"
#include <cmath>
#include <stdlib.h>
#include "pc.h"
#include "game.h"
// constructor with position, hp, attack, defense, its type and the game it in.
Merchant::Merchant(int x,int y,Game *game):
    Monster(x,y,30,70,5,game,'M'){}
// destructor
Merchant::~Merchant(){}

// Called when merchant got attack. Taking off its hp and set it to hostile.
void Merchant::defend(int hp){
game->matt();
addHP(hp);
}

// Attack pc if hostile.
void Merchant::attack(PC * pc){
if(game->mattla()){
int i=rand() % 2;
if(i==0){
int d=pc->getDEF();
int a=this->getATT();
int hp=ceil(a * 100/(100+d));
pc->addHP(-hp);
std::string s = "";
std::string acc;
std::stringstream ss;
ss << type;
ss >> acc;
s = s + acc + " deals ";
std::stringstream sss;
sss << hp;
sss >> acc;
s = s + acc + " damage to PC. ";
notify(s);
} else {
    std::string s = "";
    std::stringstream ss;
    ss << type;
    ss >> s;
    s =s + " missed the hit. ";
    notify(s);
}
}
}

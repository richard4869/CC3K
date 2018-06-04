#include "monster.h"
#include "game.h"
#include "pc.h"
#include <stdlib.h>
#include <cmath>
#include <sstream>
// constructor with its position, hp, attack, defense, type and the game it in.
Monster::Monster(int x,int y,int hp,int att,int def,Game *game,char type):
    Character(x,y,hp,att,def,game),
    type(type){}

// Called when the monster is dead and notify the game.
void Monster::dead(){
game->monsterdead(this);
}

// Return the type of the monster.
char Monster::gettype(){
return type;
}
// Notify game when sentences should be printed.
void Monster::notify(std::string s){
    game->notify(s);
}
// Attack pc with no special effects. Have 50% chance to miss the hit.
void Monster::attack(PC* pc){
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
    s =s + " missed the hit." + " ";
    notify(s);
}
}
// Notify the monster to change its hp.
void Monster::defend(int hp){
addHP(hp);
}
// Change the monster's hp by j. Notify if the monster is dead.
void Monster::addHP(int j){
HP=HP+j;
if(HP>maxHP){
    HP=maxHP;
}else if(HP<=0){
HP=0;
dead();
}
}
// destructor.
Monster::~Monster(){}

// virtual function for dragon.
void Monster::returndragon(){
}
// virtual function for dragon.
void Monster::dragonmove(PC * pc){}

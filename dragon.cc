#include "monster.h"
#include "dragon.h"
#include <stdlib.h>
#include <cmath>
#include "pc.h"
#include "game.h"
// constructor with position, hp, attack, defense, its type and the game it in.
// Having a field to record if the pc reached 1 block around dragon or dragon hoard.

Dragon::Dragon(int x,int y,Game *game):
    Monster(x,y,150,20,20,game,'D'),
    hostile(false){}
// destructor
Dragon::~Dragon(){}

// Take off the hp when dragon got attacked and set hostile to true.
void Dragon::defend(int hp){
addHP(hp);
hostile=true;
}

// Attacking pc when dragon needs to. Having a 50% to miss that hit.
void Dragon::attack(PC * pc){
if(hostile){
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
}}}

// return the address of this dragon.
void Dragon::returndragon(){
game->matchdragon(this);
}

// Move after pc's turn. Attacking pc when pc reached 1 block around dragon or dragon hoard.
void Dragon::dragonmove(PC * pc){
if(dragonhoard!=NULL){
int px = pc->getx();
int py = pc->gety();
int gx=dragonhoard->getx();
int gy=dragonhoard->gety();
    if((px - x <= 1 && px - x >= -1 && py - y <= 1 && py - y >= -1)||
        (px - gx <= 1 && px - gx >= -1 && py - gy <= 1 && py - gy >= -1)){
                hostile=true;
                attack(pc);
                }
}}

// Change the dragon hp and make its hoard be able to be picked.
void Dragon::addHP(int j){
HP=HP+j;
if(HP>=maxHP){
    HP=maxHP;
}else if(HP<=0){
dragonhoard->linked=false;
HP=0;
dead();
}
}

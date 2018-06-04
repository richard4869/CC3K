#include "monster.h"
#include "orc.h"
#include "pc.h"
#include <cmath>
#include <stdlib.h>
// constructor with position, hp, attack, defense, its type and the game it in.
Orc::Orc(int x,int y,Game *game):
    Monster(x,y,180,30,25,game,'O'){}
// destructor.
Orc::~Orc(){}

// Attack goblin with 50% bonus damage. Have 50% change to miss the hit.
void Orc::attack(PC * pc){
int i=rand() % 2;
if(i==0){
int d=pc->getDEF();
int a=this->getATT();
int hp;
if(pc->gettype()=='g'){
hp=ceil(a * 100/(100+d)) * 1.5;
} else {
hp=ceil(a * 100/(100+d));
}
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

#include "monster.h"
#include "elf.h"
#include "pc.h"
#include <cmath>
#include <stdlib.h>
#include <sstream>
#include <string>
// constructor with position, hp, attack, defense, its type and the game it in.
Elf::Elf(int x,int y,Game *game):
    Monster(x,y,140,30,10,game,'E'){}
//destructor
Elf::~Elf(){}

// Attack pc if pc is not dwarf. Have 50% to miss the hit.
void Elf::attack(PC * pc){
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
}if(pc->gettype() != 'd'){
i=rand() % 2;
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
s = s + acc + " attacks again and deals ";
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
    s =s + " attacks again and missed the hit. ";
    notify(s);
}}}

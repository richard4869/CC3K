#include "pc.h"
#include "game.h"
#include "monster.h"
#include <cmath>
#include <string>
#include <stdlib.h>
using namespace std;
// constructor with pc's position, hp, defense, attack , type and the game it in.
PC::PC(int x,int y,int hp,int att,int def,Game *game,char type):
    Character(x,y,hp,att,def,game),
    boostDEF(0),
    boostATT(0),
    gold(0),
    type(type){
    int i=0;
    while(i<6){
        knownpotn[i]=false;
        i++;
    }
    }
// Notify game that PC is dead.
void PC::dead(){
game->PCdead();
}
// get the boolean to check of the potion has been taken.
bool PC::eaten(int t){
return knownpotn[t];
}
// get the gold amount pc holds.
int PC::getgold(){
return gold;
}
// get the type of the pc.
char PC::gettype(){
return type;
}
// Notify the sentences.
void PC::notify(string s){
game->notify(s);
}
// return ah of the pc. Notify game if pc's hp lower or equal then 0.
void PC::addHP(int j){
HP=HP+j;
if(HP>maxHP){
    HP=maxHP;
}
if(HP<=0){
HP=0;
dead();
}
}
// return the actual attack of the pc.
int PC::getATT(){
if(ATT+boostATT < 0) return 0;
return ATT+boostATT;
}

// return the actual defense of the pc.

int PC::getDEF(){
if(DEF+boostDEF < 0) return 0;
return DEF+boostDEF;
}
// Add the attack of the pc.
void PC::addATT(int i){
boostATT+=i;
if(ATT+boostATT < 0) boostATT = -ATT;
}
// Add the defense of the pc.
void PC::addDEF(int i){
boostDEF+=i;
if(DEF+boostDEF < 0) boostDEF = -DEF;
}
// reset the boost when needed like go downstairs.
void PC::resetboost(){
boostATT=0;
boostDEF=0;
}
// PC get the money of value m.
void PC::getmoney(int m){
gold+=m;
}
// Take potion and set the effects. Make the potion known when see it next time.
void PC::takepotion(Potion *potn){
int t=potn->gettype();
int i=5;
int j=10;
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
// virtual function for all pc's subclass. Attacking Halfling will have 50% chance miss the hit.
void PC::attack(Monster * mostr){
if(mostr->gettype()=='L'){
    int i=rand() % 2;
    if(i==0){
        int d=mostr->getDEF();
        int a=this->getATT();
        int hp=ceil(a * 100/(100+d));
        string acc = "";
        string s;
        stringstream ss;
        ss << hp;
        ss >> acc;
        s =  "PC deals " + acc +" damage to ";
        char type = mostr->gettype();
        stringstream sss;
        sss << type;
        sss >> acc;
        s = s + acc + " (";
        int mhp = mostr->getHP();
        stringstream ssss;
        ssss << mhp;
        ssss >> acc;
        s = s + acc + " HP). ";
        notify(s);
        mostr->defend(-hp);
    } else {
        notify("PC missed the hit. ");
    }
    }
else{
int d=mostr->getDEF();
int a=this->getATT();
int hp=ceil(a * 100/(100+d));
        string acc = "";
        string s;
        stringstream ss;
        ss << hp;
        ss >> acc;
        s =  "PC deals " + acc +" damage to ";
        char type = mostr->gettype();
        stringstream sss;
        sss << type;
        sss >> acc;
        s = s + acc + " (";
        int mhp = mostr->getHP();
        stringstream ssss;
        ssss << mhp;
        ssss >> acc;
        s = s + acc + " HP). ";
        notify(s);
        mostr->defend(-hp);
}}
// destructor.
PC::~PC(){}

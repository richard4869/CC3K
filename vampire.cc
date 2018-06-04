#include "vampire.h"
#include <cmath>
#include "monster.h"
#include "potion.h"
#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;
// constructor with its position, type, hp and the game it in.
Vampire::Vampire(int x,int y,Game *game):
    PC(x,y,50,25,25,game,'v'){}

// add hp th the pc. Do not have a maxhp-check.
void Vampire::addHP(int j){
HP+=j;
if(HP<=0){
HP=0;
dead();
}
}
//Attack monsters will gain 5 HP when the monster is not dwarf, lose 5 hp otherwise.
void Vampire::attack(Monster * mostr){
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
        string type = "L";
        s = s + type + " (";
        int mhp = mostr->getHP();
        cout << mhp << endl;
        stringstream ssss;
        ssss << mhp;
        ssss >> acc;
        s = s + acc + " HP)";
        notify(s);
        notify(" and heals 5 HP. ");
        mostr->defend(-hp);
        addHP(5);
    } else {
        notify("PC missed the hit. ");
}}
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
        s = s + acc + " HP)";
        notify(s);
        if(type=='W'){
        addHP(-5);
        notify(" and lose 5 HP. ");
        }else{
        addHP(5);
        notify(" and heals 5 HP. ");
        }
        mostr->defend(-hp);
        }}

Vampire::~Vampire(){}

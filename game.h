#ifndef __GAME_H__
#define __GAME_H__
#include <iostream>
#include <string>
#include <sstream>
#include "floor.h"
#include "potion.h"
#include "gold.h"

class Monster;
class PC;
class Controller;
class Dragon;

class Game {
    Controller * controller;
    Floor* floor;
    PC* pc;
    int level;
    bool mertile;
    bool ifload;
public:
    std::string filename;
    char ** extra;
    void setpc(char);
    Monster** monsters;
    Gold ** golds;
    Potion ** potions;
    Game(Controller *);
    ~Game();
    int getlevel();
    void initfloor(std::string);
    //randomly initial monsters and items, need to go through each chamber and get coordinates
    //from chamber and stairs
    void movepc(std::string);      //received from controller, read pc position and
     //detect cell,detect monster and item if cell is walkable then call pc->chamove(x,y)
     //else call take potion and attack(Monster *)
    void notify(std::string s);
    //notify controller notify
    void pcattack(std::string s);
    void monster_turn();
    //loop through monsters detect their walkable area and randomly select a posn to
    //call chamove(x,y) or attack(PC *)
    void go_downstairs();
    Floor* getfloor();
    PC* getpc();
    //just delete all items and monsters and initial them again
    void usepotion(std::string);
    int getscore();
    void takegold(std::string);
    void monsterdead(Monster *);
    void PCdead();
    bool exist(int x,int y);
    void load(std::string);
    void matt();     //merchant got attacked
    bool mattla();   //return if merchant is hostile to player
    void addthings(int i,int j,char type);
    void matchdragon(Dragon *);
};

#endif

#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include <iostream>
#include "game.h"
#include "map.h"

class Controller  {
    Map* themap;
    Game* game;
public:
    int ifend;
    Controller();
    ~Controller();
    bool checkwin();
    void setgame(std::string s);
    void play(std::string s);
    void lose(int);
    void win(int);
    void notify(std::string);
};

#endif

#ifndef __CHAMBER_H__
#define __CHAMBER_H__
#include <iostream>
#include <sstream>

class Cell;
class Game;

class Chamber {
public:
    Cell** cell;
    int length;
    Chamber(int);
    ~Chamber();
    void randomchoose(char c, Game* game);
};

#endif

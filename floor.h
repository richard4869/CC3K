#ifndef __FLOOR_H__
#define __FLOOR_H__
#include <iostream>
#include <string>
#include "cell.h"
#include "chamber.h"

class Game;

class Floor {
    Chamber ** chambers;
    Cell** cell;
    int x;
    int y;
public:
    Floor();
    ~Floor();   //dtor
    int getx();
    void setx(int);
    void sety(int);
	void initnew(std::string s);
	void initload(std::string s);
    void setpcstair(Game* game);
    int gety();
    int** getadj(int, int);
    int* getcell(int, int, std::string);
    //return a list of cell adjacent to the coordinate
    void choosechamb (char c, Game* game);
    //randomly choose a chamber and call chamber->ramdomchoose
};

#endif

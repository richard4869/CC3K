#include "chamber.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "game.h"
#include "cell.h"
#include "floor.h"

using namespace std;
// new a chamber with its length..
Chamber::Chamber(int i){
    length = 0;
    cell = new Cell*[i];
}
// destructor.
Chamber::~Chamber(){
    delete[] cell;
}
// Choose a cell randomly when play a random floor game.
// Notify to the function in game to add things.
void Chamber::randomchoose(char c, Game* game){
    int i = rand() % length;
    int x = cell[i]->getx();
    int y = cell[i]->gety();
    game->addthings(x,y,c);
}


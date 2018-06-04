#include "cell.h"
// constructor with nothing.
Cell::Cell():
    x(0),
    y(0),
    type(' '){}

// set the position and the type (one of the '|', '-', '+', '#', '.') of the cell.
void Cell::init(int x, int y, char c){
    this->x = x;
    this->y = y;
    this->type = c;
}

// destructor.
Cell::~Cell(){}

// return the x-posn of the cell.
int Cell::getx(){
return x;
}
// return the y-posn of the cell.
int Cell::gety(){
return y;
}
// return the type of the cell.
char Cell::gettype(){
    return type;
}

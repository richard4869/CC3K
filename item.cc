#include "item.h"
// constructor with position.
Item::Item(int x,int y):
    x(x),
    y(y){}
//destructor.
Item::~Item(){}
// return its x posn.
int Item::getx(){
return x;
}
// return its y posn.
int Item::gety(){
return y;
}


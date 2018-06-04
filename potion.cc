#include "potion.h"

using namespace std;
// constructor with its position and type(0-6).
Potion::Potion(int x,int y,int type):
    Item(x,y),
    type(type){}
//destructor.
Potion::~Potion(){}
// return the type of the potion.
int Potion::gettype(){
    return type;
}

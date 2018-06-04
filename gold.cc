#include "gold.h"

using namespace std;
// constructor with its position and the value it holds.
Gold::Gold(int x,int y,int val):
Item(x,y),
linked(false){
this->value=val;
}
// destructor.
Gold::~Gold(){}
// return the value of the gold.
int Gold::getvalue(){
return value;
}

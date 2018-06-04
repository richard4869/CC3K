#ifndef __ITEM_H__
#define __ITEM_H__

class Item {
 int x;
 int y;
 public:
     Item(int x,int y);
     virtual ~Item() = 0;
     int getx();
     int gety();
};

#endif

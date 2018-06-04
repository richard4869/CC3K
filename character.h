#ifndef __CHARACTER_H__
#define __CHARACTER_H__
#include <iostream>
#include <sstream>

class Game;

class Character {
protected:
    int x;
    int y;
    int ATT;
    int DEF;
    int HP;
    int maxHP;
    Game* game;
    Character(int x,int y,int hp,int att,int def,Game *game);
    virtual void dead()=0;
  public:
      void setxy(int x,int y);
      int getx();
      int gety();
      virtual int getATT();
      virtual int getDEF();
      int getHP();
      void chamove(int i,int j);
      virtual ~Character()=0;
};

#endif

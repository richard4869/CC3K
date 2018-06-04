#ifndef __MAP_H__
#define __MAP_H__
#include <iostream>
#include <sstream>

class Game;

class Map {
  char ** display;
  std::string action;
  public:
      void print(Game* game);
      void notify(std::string s);
      Map(std::string name);
      ~Map();
};

#endif

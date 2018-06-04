#ifndef __CELL_H__
#define __CELL_H__


class Cell {
  int x;
  int y;
  char type;
  public:
      Cell();
      ~Cell();
      int getx();
      int gety();
      char gettype();
      void init(int, int, char);
};
#endif

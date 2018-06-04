#ifndef ROBOT_H
#define ROBOT_H

#include "pc.h"

class Game;

class Robot : public PC
{
    public:
        /** Default constructor */
        Robot(int x,int y,Game *game);
        /** Default destructor */
        virtual ~Robot();
};

#endif // ROBOT_H

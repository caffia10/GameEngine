#ifndef PLAYER_H
#define PLAYER_H

#include "Engine.h"

class Player: public Entity
{
public:
    Player(/* args */);
    ~Player();


    i8 heal = 100;
    i8 armor = 0;
};

#endif

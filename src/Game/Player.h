#ifndef PLAYER_H
#define PLAYER_H

#include "GameEngine/Interface/Engine.h"

class Player: public Entity
{
public:
    Player(/* args */);
    ~Player();


    M_PROPERTY(P_READ_ONLY) i8 heal = 100;
    M_PROPERTY(P_READ_ONLY) i8 armor = 0;
};

#endif

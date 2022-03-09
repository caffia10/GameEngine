#ifndef PLAYER_H
#define PLAYER_H

#include "Engine/Interface/Engine.h"

#define METACLASS(classType) classType
#define METACLASS(className)
#define METACLASS(className)

class  METACLASS(Player): public Entity
{
public:
    Player(/* args */);
    ~Player();

    i8 heal = 100;
    i8 armor = 0;
};

#endif

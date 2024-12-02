#pragma once
#include "drawable.h"

///////////////////////////////////////   collidable classes   /////////////////////////////////
//Base class for all collidable (objects that may collide with other objects)
class collidable :public drawable
{
public:
    collidable(point r_uprleft, int r_width, int r_height, game* r_pGame);
    static point  Collision_Check(collidable* hitbox_1, collidable* hitbox_2);
    virtual void collisionAction() = 0;    //action that should be performed upon collision
};



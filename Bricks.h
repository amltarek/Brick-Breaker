#pragma once

//This file contains all classes bricks classes 
#include "collidable.h"



enum BrickType	//add more brick types
{
	BRK_NRM,	//Normal Brick (0)
	BRK_BMB,	//Bomb Brick (1)
	BRK_RCK,	//Rock Brick (2)
	BRK_PUD,	//Powerup/down Brick (3) 
	BRK_HRD,	//Hard Brick (4)
	BRK_DB

	//TODO: Add more types
};

////////////////////////////////////////////////////  class brick  ///////////////////////////////////////
//Base class for all bricks
class brick :public collidable
{
protected:
	BrickType type;
public:
	brick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	BrickType getType() const;
};


////////////////////////////////////////////////////  class normalBrick  /////////////////////////////////
class normalBrick :public brick
{
public:
	normalBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
};

////////////////////////////////////////////////////  class bombBrick  /////////////////////////////////
class bombBrick :public brick
{
public:
	bombBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
};

////////////////////////////////////////////////////  class rockBrick  /////////////////////////////////
class rockBrick :public brick
{
public:
	rockBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
};

////////////////////////////////////////////////////  class powerup_downBrick  /////////////////////////////////
class powerup_downBrick :public brick
{

public:
	powerup_downBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
};
////////////////////////////////////////////////////  class harbrick  /////////////////////////////////

class hardBrick :public brick
{
private:
	int strength;
public:
	hardBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
};
//////////////////////////////////////////////////////////////////////

class doubleBrick :public brick
{
private:
	
public:
	doubleBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
};





#pragma once
#include "collidable.h"
#include "Bricks.h"
#include"timer.h"
class paddle :public collidable {
private:
	bool controlinverted;
	int paddleSpeed=20;
public:
	paddle(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
	void move_paddle_right();
	void reset_pos();
	void move_paddle_left();
	void inverted(bool inverted);
	bool getcontrol();
	int getSpeed();
	void setSpeed(int speed);
};

enum BallType {
	NRM_BALL,
	FIRE_BALL
};

class ball :public collidable {
private:
	BallType ballType=NRM_BALL;
public:
	ball(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
	bool move_ball();
	void get_velocity();
	void brickdeflection();
	void draw();
	void reset_position();
	BallType getType();
	void setType(BallType type);
};
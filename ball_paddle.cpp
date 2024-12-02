#include "CMUgraphicsLib\CMUgraphics.h"
#include "ball_paddle.h"
#include"collidable.h"
#include "game.h"
#include "gameConfig.h"
#include "grid.h"
#include "CMUgraphicsLib/auxil.h"
/////////////////////////////////////////Paddle///////////////////////////////////////////////
paddle::paddle(point r_uprleft, int r_width, int r_height, game* r_pGame):
	collidable(r_uprleft, r_width, r_height, r_pGame){
	imageName = "images\\paddle.jpg";
	controlinverted = false;
}


//////////////////////////////////////////////////Pddle Collisions////////////////////////////////////////////////////
void paddle::collisionAction()
{

}


/////////////////////////////////////////////////////Paddle Movement//////////////////////////////////////////////////////////////////
void paddle::move_paddle_left()
{
	if (uprLft.x - paddleSpeed >= 0)
	{
		pGame->getWind()->SetPen(LAVENDER, 1);
		pGame->getWind()->SetBrush(LAVENDER);
		pGame->getWind()->DrawRectangle(uprLft.x, uprLft.y, uprLft.x + width, uprLft.y + height);
		this->uprLft.x = uprLft.x - paddleSpeed;
		this->draw();
	}
	pGame->getWind()->UpdateBuffer();
}

void paddle::inverted(bool inverted)
{
	controlinverted = inverted;
}

bool paddle::getcontrol()
{
	return controlinverted;
}

int paddle::getSpeed()
{
	return paddleSpeed;
}

void paddle::setSpeed(int speed)
{
	this->paddleSpeed = speed;
}




void paddle::move_paddle_right()
{
	if (uprLft.x + width + paddleSpeed <= pGame->getWind()->GetWidth()) {
		pGame->getWind()->SetPen(LAVENDER, 1);
		pGame->getWind()->SetBrush(LAVENDER);
		pGame->getWind()->DrawRectangle(uprLft.x, uprLft.y, uprLft.x + width, uprLft.y + height);
		this->uprLft.x = uprLft.x + paddleSpeed;
		this->draw();
	}
	pGame->getWind()->UpdateBuffer();
}

void paddle::reset_pos() {
	pGame->getWind()->SetPen(LAVENDER);
	pGame->getWind()->SetBrush(LAVENDER);
	pGame->getWind()->DrawRectangle(uprLft.x, uprLft.y, uprLft.x+width, uprLft.y+height);
	uprLft.x = (config.windWidth / 2) - 50;
	uprLft.y = 500;
	this->draw();
}

//////////////////////////////////////////////////////////////////////Ball/////////////////////////////////////////////////////////////
ball::ball(point r_uprleft, int r_width, int r_height, game* r_pGame):
	collidable(r_uprleft, r_width, r_height, r_pGame)
{
	imageName = "images\\ball.jpg";
}

void ball::collisionAction()
{

}


bool ball::move_ball()
{

	point prevPosition = uprLft;

	pGame->getWind()->SetPen(LAVENDER);
	pGame->getWind()->SetBrush(LAVENDER);
	pGame->getWind()->DrawRectangle(prevPosition.x, prevPosition.y, prevPosition.x+30,prevPosition.y+30);
	if (uprLft.y <= 40) {
		pGame->set_direction(pGame->get_direction()[0], 1);
		uprLft.y = 40 + 1;
	}
	if (uprLft.x <=5) {
		pGame->set_direction(1, pGame->get_direction()[1]);
		uprLft.x = 6;
	}
	if (uprLft.x >= 1150) {
		pGame->set_direction(-1, pGame->get_direction()[1]);
		uprLft.x = 1149;
	}
	if (uprLft.y >= 520) {
		pGame->set_direction(0, 0);
		return false;
	}
	uprLft.y += pGame->get_direction()[1]*2;
	uprLft.x += pGame->get_direction()[0]*2;

	pGame->getGrid()->draw_lines();
	pGame->getpaddle()->draw();
	this->draw();
	pGame->getWind()->UpdateBuffer();
	Pause(1);
	return true;
}

void ball::get_velocity()
{
	paddle* thepaddle = pGame->getpaddle();
	point z = Collision_Check(this, thepaddle);
	float pos_onpaddle = z.x - thepaddle->getPosition().x;
	if (z.x != 0 && z.y != 0) {
		
			int z = abs(pos_onpaddle - 50);
			int newy=2;
			switch (z/10)
			{
			case (1): { newy = 2; }
					break;
			case(2): {newy = 3; }
					break;
			case(3): {newy = 4; }
				   break;
			case(4): {newy = 6; }
				   break;
			default:
				break;
			}
		if (pos_onpaddle > 50) {
			pGame->set_direction(2, -newy);
		}
		else {
			pGame->set_direction(-2, -newy);
		}

	}

}

void ball::brickdeflection() {
	grid* pGrid = pGame->getGrid();
	brick*** matrix = pGrid->get_matrix();
	for (int i = 0; i < pGrid->get_rows(); i++)
		for (int j = 0; j < pGrid->get_cols(); j++)
			if (matrix[i][j]) {
				brick* current_brick = matrix[i][j];
				point y = Collision_Check(this, current_brick);
				float pos_onbrick = y.x - current_brick->getPosition().x;
				int newy = 2;
				if (y.x != 0 && y.y != 0) {

					int z = abs(pos_onbrick - 30);
					
					switch (z / 10)
					{
					case (1): { newy = 2; }
							break;
					case(2): {newy = 3; }
						   break;
					case(3): {newy = 4; }
						   break;
					case(4): {newy = 6; }
						   break;
					default:
						break;
					}
				}
				if (pos_onbrick!=0.0 &&y.x!=0&&y.y!=0){
					if (pos_onbrick > 30) {
						pGame->set_direction(2, -newy*pGame->get_direction()[1]/abs(pGame->get_direction()[1]));
					}
					else {
						pGame->set_direction(-2, -newy);
					}
				}
				else if(y.x!=0&&y.y!=0) {
					pGame->set_direction(-(pGame->get_direction()[0]), pGame->get_direction()[1]);
				}
			}

}

void ball::draw()
{
	if (ballType == NRM_BALL) {
		pGame->getWind()->SetPen(BLUE);
		pGame->getWind()->SetBrush(BLUE);
	}
	else {
		pGame->getWind()->SetPen(RED);
		pGame->getWind()->SetBrush(RED);
	}
	pGame->getWind()->DrawCircle(uprLft.x+15, uprLft.y+15, 15);
}

void ball::reset_position()
{
	pGame->getGameToolbar()->drawPlayMode();
	this->uprLft.x = (config.windWidth / 2) - 15;
	this->uprLft.y = pGame->getpaddle()->getPosition().y-30;
	pGame->set_direction(0, -1);
	this->draw();
	pGame->getpaddle()->reset_pos();
}

BallType ball::getType()
{
	return ballType;
}

void ball::setType(BallType type)
{
	this->ballType = type;
}


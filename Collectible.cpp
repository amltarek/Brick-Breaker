#include "collectible.h"


collectible::collectible(point r_uprleft, int r_radius, game* r_pGame,int r_duration) :
    collidable(r_uprleft, r_radius * 2, r_radius * 2, r_pGame),duration(r_duration)
    
{
}



bool collectible::move_collectible()
{
	point prevPosition = uprLft;
	pGame->getWind()->SetPen(LAVENDER);
	pGame->getWind()->SetBrush(LAVENDER);
	pGame->getWind()->DrawRectangle(prevPosition.x, prevPosition.y, prevPosition.x + 30, prevPosition.y + 30);
	uprLft.y++;
	pGame->getpaddle()->draw();
	this->draw();
	pGame->getWind()->UpdateBuffer();
	if (prevPosition.y >= 520) {
		pGame->removecollectibles(this->getindex());
		return false;
	}
	return true;
}
void collectible::setindex(int index)
{
	this->index = index;
}
int collectible::getindex()
{
	return index;
}

bool collectible::ismoving()
{
	return moving;
}

int collectible::get_timer()
{
	collectibleTimer.update_time();
	return collectibleTimer.get_time();
}

int collectible::get_duration()
{
	return duration;
}

bool collectible::get_activation()
{
	return activated;
}

fireball::fireball(point r_uprleft, int r_radius, game* r_pGame,int r_duration):
	collectible(r_uprleft, r_radius, r_pGame, r_duration) {
	imageName = "images\\collectibles\\Fireball.jpg";
}

void fireball::collisionAction()
{
	
	moving = false;
	activated = true;
	collectibleTimer.set_time();
	point prevPosition = uprLft;
	pGame->getWind()->SetPen(LAVENDER);
	pGame->getWind()->SetBrush(LAVENDER);
	pGame->getWind()->DrawRectangle(prevPosition.x, prevPosition.y, prevPosition.x + 30, prevPosition.y + 30);
	pGame->getball()->setType(FIRE_BALL);
}

void fireball::stopAction()
{
	pGame->getball()->setType(NRM_BALL);
	pGame->removecollectibles(this->getindex());
}

invertedPaddle::invertedPaddle(point r_uprleft, int r_radius, game* r_pGame,int r_duration):
	collectible(r_uprleft, r_radius, r_pGame,r_duration) {
	imageName = "images\\collectibles\\inverted paddle.jpg";
}

void invertedPaddle::collisionAction()
{
	moving = false;
	activated = true;
	collectibleTimer.set_time();
	point prevPosition = uprLft;
	pGame->getWind()->SetPen(LAVENDER);
	pGame->getWind()->SetBrush(LAVENDER);
	pGame->getWind()->DrawRectangle(prevPosition.x, prevPosition.y, prevPosition.x + 30, prevPosition.y + 30);
	pGame->getpaddle()->inverted(true);
}

void invertedPaddle::stopAction()
{
	pGame->getpaddle()->inverted(false);
	pGame->removecollectibles(this->getindex());
}

Windglide::Windglide(point r_uprleft, int r_radius, game* r_pGame, int r_duration) :
	collectible(r_uprleft, r_radius, r_pGame, r_duration) {
	imageName = "images\\collectibles\\Windglide.jpg";
}

void Windglide::collisionAction()
{
	moving = false;
	activated = true;
	collectibleTimer.set_time();
	point prevPosition = uprLft;
	pGame->getWind()->SetPen(LAVENDER);
	pGame->getWind()->SetBrush(LAVENDER);
	pGame->getWind()->DrawRectangle(prevPosition.x, prevPosition.y, prevPosition.x + 30, prevPosition.y + 30);
	pGame->getpaddle()->setSpeed(40);
}

void Windglide::stopAction()
{
	pGame->getpaddle()->setSpeed(30);
	pGame->removecollectibles(this->getindex());
}

Quicksand::Quicksand(point r_uprleft, int r_radius, game* r_pGame, int r_duration) :
	collectible(r_uprleft, r_radius, r_pGame, r_duration) {
	imageName = "images\\collectibles\\Quicksand.jpg";
}

void Quicksand::collisionAction()
{
	moving = false;
	activated = true;
	collectibleTimer.set_time();
	point prevPosition = uprLft;
	pGame->getWind()->SetPen(LAVENDER);
	pGame->getWind()->SetBrush(LAVENDER);
	pGame->getWind()->DrawRectangle(prevPosition.x, prevPosition.y, prevPosition.x + 30, prevPosition.y + 30);
	pGame->getpaddle()->setSpeed(10);
}

void Quicksand::stopAction()
{
	pGame->getpaddle()->setSpeed(30);
	pGame->removecollectibles(this->getindex());
}



freeze::freeze(point r_uprleft, int r_radius, game* r_pGame, int r_duration) :
	collectible(r_uprleft, r_radius, r_pGame, r_duration)
{
	imageName = "images\\collectibles\\freeze.jpg";
}

void freeze::collisionAction()
{
	moving = false;
	activated = true;
	collectibleTimer.set_time();
	point prevPosition = uprLft;
	pGame->getWind()->SetPen(LAVENDER);
	pGame->getWind()->SetBrush(LAVENDER);
	pGame->getWind()->DrawRectangle(prevPosition.x, prevPosition.y, prevPosition.x + 30, prevPosition.y + 30);
	direction = pGame->get_direction();
	pGame->set_direction(0, 0);
}

void freeze::stopAction()
{	
	pGame->set_direction(direction[0],direction[1]);
	pGame->removecollectibles(this->getindex());
}

widepaddle::widepaddle(point r_uprleft, int r_radius, game* r_pGame, int r_duration):
	collectible(r_uprleft, r_radius, r_pGame, r_duration)
{
	imageName = "images\\collectibles\\widepaddle.jpg";

}

void widepaddle::collisionAction()
{

}

void widepaddle::stopAction()
{
}

magnet::magnet(point r_uprleft, int r_radius, game* r_pGame, int r_duration)
	:collectible(r_uprleft, r_radius, r_pGame, r_duration)
{

	imageName = "images\\collectibles\\magnet.jpg";
}

void magnet::collisionAction()
{
	pGame->getGrid()->draw();
	pGame->getWind()->SetPen(LAVENDER);
	pGame->getWind()->SetBrush(LAVENDER);
	pGame->getWind()->DrawRectangle(pGame->getball()->getPosition().x, pGame->getball()->getPosition().y, pGame->getball()->getPosition().x + 30, pGame->getball()->getPosition().y + 30);
	pGame->getball()->reset_position();
	
	pGame->removecollectibles(this->getindex());

}

void magnet::stopAction()
{


}

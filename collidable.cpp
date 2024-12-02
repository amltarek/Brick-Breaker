#include "collidable.h"

collidable::collidable(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	drawable(r_uprleft, r_width, r_height, r_pGame)
{
}
point collidable::Collision_Check(collidable* hitbox_1, collidable* hitbox_2)
{
	point collision_point;
	collision_point.x = 0;
	collision_point.y = 0;
	int x_1 = (hitbox_1->uprLft).x;
	int y_1 = (hitbox_1->uprLft).y;
	int x_2 = (hitbox_2->uprLft).x;
	int y_2 = (hitbox_2->uprLft).y;
	int height_1 = hitbox_1->height;
	int height_2 = hitbox_2->height;
	int width_1 = hitbox_1->width;
	int width_2 = hitbox_2->width;

	if (x_1 + width_1 >= x_2 && x_1 - width_2 <= x_2 && y_1 - y_2 <= height_1 && y_2 - y_1 <= height_2) {
		hitbox_1->collisionAction();
		hitbox_2->collisionAction();
		if (x_2 - x_1 == width_1) {
			collision_point.x = x_2;
			if (y_1 > y_2) {
				collision_point.y = y_2 - (height_1 - (y_1 - y_2)) / 2;
			}
			else {
				if (y_2 - y_1 + height_1 > height_2) collision_point.y = y_1 - (height_2 - (y_2 - y_1)) / 2;
				else collision_point.y = y_2 - (y_2 - y_1 + height_1 / 2);
			}
		}
		if (x_2 - x_1 < width_1 && x_1 - x_2 < width_2) {
			if (x_1 < x_2) collision_point.x = x_2 + (width_1 - (x_2 - x_1)) / 2;
			if (x_1 > x_2 && x_1 <= x_2 + width_2 - width_1) collision_point.x = x_1 + width_1 / 2;
			if (x_1 > x_2 + width_2 - width_1) collision_point.x = x_1 + (width_2 - (x_1 - x_2)) / 2;
			if (y_1 > y_2) collision_point.y = y_2;
			if (y_1 < y_2) collision_point.y = y_1;
		}
		if (x_1 - x_2 == width_2) {
			collision_point.x = x_1;
			if (y_1 > y_2) {
				collision_point.y = y_2 - (height_1 - (y_1 - y_2)) / 2;
			}
			else {
				if (y_2 - y_1 + height_1 > height_2) collision_point.y = y_1 - (height_2 - (y_2 - y_1)) / 2;
				else collision_point.y = y_2 - (y_2 - y_1 + height_1 / 2);
			}
		}
		return collision_point;
	}
	else {
		return collision_point;
	}

}
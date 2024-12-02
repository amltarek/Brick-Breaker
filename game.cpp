#include "game.h"
#include "gameConfig.h"
#include <chrono>
#include <thread>
#include "grid.h"
#include "Collectible.h"
#include "collidable.h"
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;
class collidable;
game::game()
{



	//Initialize playgrond parameters
	gameMode = MODE_DSIGN;

	//1 - Create the main window
	pWind = CreateWind(config.windWidth, config.windHeight, config.wx, config.wy);

	//2 - create and draw the toolbar
	point toolbarUpperleft;
	toolbarUpperleft.x = 0;
	toolbarUpperleft.y = 0;
	

	gameToolbar = new toolbar(toolbarUpperleft,0,config.toolBarHeight, this);
	gameToolbar->drawDesignMode();

	//3 - create and draw the grid
	point gridUpperleft;
	gridUpperleft.x = 0;
	gridUpperleft.y = config.toolBarHeight;
	bricksGrid = new grid(gridUpperleft, config.windWidth, config.gridHeight, this);
	bricksGrid->draw();
	
	//4- Create the Paddle
	//TODO: Add code to create and draw the paddle
	point uperleft;
	uperleft.x = (config.windWidth/2)-50;
	uperleft.y = 500;
	int paddle_width = 100;
	int paddle_height = 30;
	temppaddle= new paddle(uperleft, paddle_width, paddle_height, this);
	temppaddle->draw();
	//5- Create the ball
	//TODO: Add code to create and draw the ball
	point position;
	position.x =(config.windWidth/2)-15;
	position.y = temppaddle->getPosition().y-30;
	tempball = new ball(position, 30, 30, this);
	
	//ball_paddle[0]->draw();
	//6- Create and clear the status bar
	gameCollectibles = new collectible * [maxcollect];
	clearStatusBar();
}

game::~game()
{
	delete pWind;
	delete gameToolbar;
	delete bricksGrid;
}


clicktype game::getMouseClick(int& x, int& y) const
{
	return pWind->WaitMouseClick(x, y);	//Wait for mouse click
}
clicktype game::getMouseClickc(int& x, int& y) const
{
	return pWind->GetMouseClick(x, y);	//Wait for mouse click
}
keytype game::wait_key(char& x) const
{
	return pWind->WaitKeyPress(x);
}
keytype game::get_key(char& x) const
{
	return pWind->GetKeyPress(x);
}
//////////////////////////////////////////////////////////////////////////////////////////
window* game::CreateWind(int w, int h, int x, int y) const
{
	window* pW = new window(w, h, x, y);
	pW->SetBrush(config.bkGrndColor);
	pW->SetPen(config.bkGrndColor, 1);
	pW->DrawRectangle(0, 0, w, h);
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void game::clearStatusBar() const
{
	//Clear Status bar by drawing a filled rectangle
	pWind->SetPen(config.statusBarColor, 1);
	pWind->SetBrush(config.statusBarColor);
	pWind->DrawRectangle(0, config.windHeight - config.statusBarHeight, config.windWidth, config.windHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////

void game::printMessage(string msg) const	//Prints a message on status bar
{
	clearStatusBar();	//First clear the status bar

	pWind->SetPen(config.penColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, config.windHeight - (int)(0.85 * config.statusBarHeight), msg);
}



window* game::getWind() const		//returns a pointer to the graphics window
{
	return pWind;
}

void game::setGameMode(int gamemode)
{
	this->gameMode = MODE(gamemode);
}



string game::getString() const
{
	string Label;
	char Key;
	keytype ktype;
	pWind->FlushKeyQueue();
	while (1)
	{
		ktype = pWind->WaitKeyPress(Key);
		if (ktype == ESCAPE)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if (Key == 8)	//BackSpace is pressed
			if (Label.size() > 0)
				Label.resize(Label.size() - 1);
			else
				Key = '\0';
		else
			Label += Key;
		printMessage(Label);
	}
}



grid* game::getGrid() const
{
	// TODO: Add your implementation code here.
	return bricksGrid;
}

toolbar* game::getGameToolbar() const
{
	return gameToolbar;
}

ball* game::getball() const
{
	return tempball;
}

paddle* game::getpaddle() const
{
	return temppaddle;
}


int game::getScore()
{
	return score;
}

void game::reset_game()
{
	for (int i = 0; i < bricksGrid->get_rows(); i++)
		for (int j = 0; j < bricksGrid->get_cols(); j++)
			if (bricksGrid->get_matrix()[i][j]) {
				bricksGrid->deleteBrick(bricksGrid->get_matrix()[i][j]->getPosition());
			}
	
	bricksGrid->draw();
	getWind()->SetPen(LAVENDER);
	getWind()->SetBrush(LAVENDER);
	getWind()->DrawRectangle(tempball->getPosition().x, tempball->getPosition().y, tempball->getPosition().x + 30, tempball->getPosition().y + 30);
	tempball->reset_position();
	score = 0;
	timer = 0;
	gameToolbar->reset_lives();

}





void game::updateScore(int scoreChange)
{
	score += scoreChange;
	gameToolbar->draw_score();
}


void game::addcollectibles(point uprleft)
{
	int collectible_radius = 7;
	if (currentcollect < maxcollect)
	{
		int random = rand() % (int(CLTB_CNT)); 

		switch (random)
		{
		case 0:
			gameCollectibles[currentcollect] = new fireball(uprleft, collectible_radius, this,20);
			break;
		case 1:
			gameCollectibles[currentcollect] = new invertedPaddle(uprleft, collectible_radius, this,20);
			break;
		case 2:
			gameCollectibles[currentcollect] = new Windglide(uprleft, collectible_radius, this, 20);
			break;
		case 3:
			gameCollectibles[currentcollect] = new Quicksand(uprleft, collectible_radius, this, 20);
			break;
		case 4:
			gameCollectibles[currentcollect] = new freeze(uprleft, collectible_radius, this, 8);
			break;
		case 5:
			gameCollectibles[currentcollect] = new magnet(uprleft, collectible_radius, this, 3);
			break;

		}

		gameCollectibles[currentcollect]->setindex(currentcollect);
		currentcollect++;
	}
}

void game::removecollectibles(int index)
{
	getWind()->SetBrush(LAVENDER);
	getWind()->SetPen(LAVENDER);
	int x = gameCollectibles[index]->getPosition().x;
	int y = gameCollectibles[index]->getPosition().y;
	getWind()->DrawRectangle(x - 30, y - 30, x + 30, y + 30);
	delete gameCollectibles[index];
	gameCollectibles[index] = nullptr;
}

void game::set_direction(float x, float y)
{
	direction[0] = x;
	direction[1] = y;
}

float* game::get_direction()
{
	return direction;
}

void game::add_time()
{
	collectible_times[currentcollect].set_time();
}

void game::setWinStatus(bool p)
{
	this->win = p;
}


////////////////////////////////////////////////////////////////////////
void game::go() const
{
	//This function reads the position where the user clicks to determine the desired operation
	int x, y;
	bool isExit = false;
	char paddle_movement;
	char moveball;
	keytype ktype;
	keytype space;
	//Change the title
	pWind->ChangeTitle("- - - - - - - - - - Brick Breaker (CIE202-project) - - - - - - - - - -");
	do
	{
		if (gameMode == MODE_DSIGN)		//Game is in the Desgin mode
		{
			printMessage("Ready...");
			getMouseClick(x, y);	//Get the coordinates of the user click
			//[1] If user clicks on the Toolbar
			pWind->SetBrush(LAVENDER);
			if (y >= 0 && y < config.toolBarHeight)
			{
				isExit = gameToolbar->handleClickDesignMode(x, y);
			}
		}
		if (gameMode == MODE_PLAY) {  //Game is in the Play mode
			space = wait_key(moveball);
			temppaddle->draw();
			while (moveball == ' '&& gameMode==MODE_PLAY) {
				do {
					bricksGrid->checkBrickDestruction();
					gameToolbar->draw_time(pWind);
					if (!tempball->move_ball()) {
						gameToolbar->decrease_lives();
						tempball->reset_position();
						temppaddle->draw();
						space = wait_key(moveball);
					}
					if (tempball->getPosition().y>400)
						tempball->get_velocity();
					else
						tempball->brickdeflection();
					for (int i = 0; i < currentcollect; i++) {
						if (gameCollectibles[i]&&gameCollectibles[i]->ismoving()) {
							gameCollectibles[i]->move_collectible();
							if (gameCollectibles[i])
							collidable::Collision_Check(gameCollectibles[i], temppaddle);
						}
						else if (gameCollectibles[i] && gameCollectibles[i]->get_activation()) {
							if (gameCollectibles[i]->get_timer() >= gameCollectibles[i]->get_duration()) {
								gameCollectibles[i]->stopAction();
							}
						}
					}
					
					ktype = get_key(paddle_movement);
					if (ktype == ESCAPE) {
						printMessage("Toolbar accessed");
						getMouseClick(x, y);
						if (y >= 0 && y < config.toolBarHeight)
						{
							isExit = gameToolbar->handleClickPlayMode(x, y);
							ktype = NO_KEYPRESS;
						}
					}
				} while (ktype != ARROW && gameMode==MODE_PLAY);
				printMessage("Play                                                                                                                                              Press Esc to access toolbar");
				while (ktype == ARROW) {

					if (getpaddle()->getcontrol()) {
						if (paddle_movement == 6) {
							temppaddle->move_paddle_left();
						}
						if (paddle_movement == 4) {
							temppaddle->move_paddle_right();
						}
					}
					else {
						if (paddle_movement == 6) {
							temppaddle->move_paddle_right();
						}
						if (paddle_movement == 4) {
							temppaddle->move_paddle_left();
						}


					}
					
					ktype = NO_KEYPRESS;

				} 

			}
		}
		if (gameMode == MODE_END)		//Game ended
		{
			string message;
			if (win) message = "Congratulations!";
			else message = "Game Over!";
			pWind->DrawRectangle(200, 100, 1000, 500);
			pWind->SetPen(config.penColor, 50);
			pWind->SetFont(24, BOLD, BY_NAME, "Arial");
			pWind->DrawString(530, 200, message);
			pWind->DrawString(300, 300, "Time taken: "+ to_string(gameToolbar->times.get_time()));
			pWind->DrawString(750, 300, "Total score: " + to_string(score));
			wait_key(moveball);
		}
	} while (!isExit);
	pWind->SetBuffering(false);
}
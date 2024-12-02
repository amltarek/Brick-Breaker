#include "toolbar.h"
#include "game.h"
#include "grid.h"
#include "gameConfig.h"
#include <ctime>


////////////////////////////////////////////////////  class toolbarIcon   ////////////////////////////////////////////////////
toolbarIcon::toolbarIcon(point r_uprleft, int r_width, int r_height, game* r_pGame):
	drawable(r_uprleft, r_width, r_height,  r_pGame)
{}




////////////////////////////////////////////////////  class iconAddNormalBrick   //////////////////////////////////////////////
iconAddNormalBrick::iconAddNormalBrick(point r_uprleft, int r_width, int r_height, game* r_pGame):
	toolbarIcon(r_uprleft, r_width, r_height,  r_pGame)
{}

void iconAddNormalBrick::onClick()
{
	
	pGame->printMessage("Click on empty cells to add Normal Bricks  ==> Right-Click to stop <==");
	int x, y;
	clicktype t = pGame->getMouseClick(x, y);
	while (t == LEFT_CLICK)
	{
		point clicked;
		clicked.x = x;
		clicked.y = y;
		grid* pGrid = pGame->getGrid();
		pGrid->addBrick(BRK_NRM, clicked);
		pGrid->draw();
		t = pGame->getMouseClick(x, y);
	}
	pGame->printMessage("");

}

////////////////////////////////////////////////////  class iconAddBombBrick   //////////////////////////////////////////////
iconAddBombBrick::iconAddBombBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconAddBombBrick::onClick()
{

	pGame->printMessage("Click on empty cells to add Bomb Bricks  ==> Right-Click to stop <==");
	int x, y;
	clicktype t = pGame->getMouseClick(x, y);
	while (t == LEFT_CLICK)
	{
		point clicked;
		clicked.x = x;
		clicked.y = y;
		grid* pGrid = pGame->getGrid();
		pGrid->addBrick(BRK_BMB, clicked);
		pGrid->draw();
		t = pGame->getMouseClick(x, y);
	}
	pGame->printMessage("");

}

////////////////////////////////////////////////////  class iconAddRockBrick   //////////////////////////////////////////////
iconAddRockBrick::iconAddRockBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconAddRockBrick::onClick()
{

	pGame->printMessage("Click on empty cells to add Rock Bricks  ==> Right-Click to stop <==");
	int x, y;
	clicktype t = pGame->getMouseClick(x, y);
	while (t == LEFT_CLICK)
	{
		point clicked;
		clicked.x = x;
		clicked.y = y;
		grid* pGrid = pGame->getGrid();
		pGrid->addBrick(BRK_RCK, clicked);
		pGrid->draw();
		t = pGame->getMouseClick(x, y);
	}
	pGame->printMessage("");

}

////////////////////////////////////////////////////  class iconAddPowerup_downBrick   //////////////////////////////////////////////
iconAddPowerup_downBrick::iconAddPowerup_downBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconAddPowerup_downBrick::onClick()
{

	pGame->printMessage("Click on empty cells to add Powerup/down Bricks  ==> Right-Click to stop <==");
	int x, y;
	clicktype t = pGame->getMouseClick(x, y);
	while (t == LEFT_CLICK)
	{
		point clicked;
		clicked.x = x;
		clicked.y = y;
		grid* pGrid = pGame->getGrid();
		pGrid->addBrick(BRK_PUD, clicked);
		pGrid->draw();
		t = pGame->getMouseClick(x, y);
	}
	pGame->printMessage("");

}

////////////////////////////////////////////////////Class iconAddhardbrick/////////////////////////////////////////////////////////////
iconAddhardBrick::iconAddhardBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconAddhardBrick::onClick()
{

	pGame->printMessage("Click on empty cells to add Hard Bricks  ==> Right-Click to stop <==");
	int x, y;
	clicktype t = pGame->getMouseClick(x, y);
	while (t == LEFT_CLICK)
	{
		point clicked;
		clicked.x = x;
		clicked.y = y;
		grid* pGrid = pGame->getGrid();
		pGrid->addBrick(BRK_HRD, clicked);
		pGrid->draw();
		t = pGame->getMouseClick(x, y);
	}
	pGame->printMessage("");

}

/////////////////////////////////////////////////////////////////////////////////////////////////

iconAdddoublebrick::iconAdddoublebrick(point r_uprleft, int r_width, int r_height, game* r_pGame)
	:toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{

}

void iconAdddoublebrick::onClick()
{
	pGame->printMessage("Click on empty cells to add swap Bricks  ==> Right-Click to stop <==");
	int x, y;
	clicktype t = pGame->getMouseClick(x, y);
	while (t == LEFT_CLICK)
	{
		point clicked;
		clicked.x = x;
		clicked.y = y;
		grid* pGrid = pGame->getGrid();
		pGrid->addBrick(BRK_DB, clicked);
		pGrid->draw();
		t = pGame->getMouseClick(x, y);
	}
	pGame->printMessage("");


}


////////////////////////////////////////////////////  class iconDelete   //////////////////////////////////////////////
iconDelete::iconDelete(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconDelete::onClick()
{
	//Allow to delete on left-click of brick, till right click is pressed
	pGame->printMessage("Click on any placed brick to delete it  ==> Right-Click to stop <==");
	int x, y;
	clicktype t = pGame->getMouseClick(x, y);
	while (t == LEFT_CLICK)
	{
		point clicked;
		clicked.x = int(x/60)*60;
		clicked.y = int((y-40)/30)*30+40;
		grid* pGrid = pGame->getGrid();
		pGame->getWind()->SetBrush(LAVENDER);
		pGame->getWind()->SetPen(LAVENDER);
		pGrid->deleteBrick(clicked);
		t = pGame->getMouseClick(x, y);
	}
	pGame->printMessage("");
}

////////////////////////////////////////////////////  class iconLoad   //////////////////////////////////////////////
iconLoad::iconLoad(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconLoad::onClick()
{
	//TO DO: add code for loading grid from file (Check I/O lab)
	pGame->printMessage("Enter file name to load design from:");
	string filename = pGame->getString();
	pGame->getGrid()->loadFromFile(filename);
}


////////////////////////////////////////////////////  class iconSave   //////////////////////////////////////////////
iconSave::iconSave(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconSave::onClick()
{
	//TO DO: add code for saving grid to file (Check I/O lab)
	pGame->printMessage("Enter file name to save design in:");
	string filename = pGame->getString();
	pGame->getGrid()->saveToFile(filename);
}


////////////////////////////////////////////////////  class iconPlay   //////////////////////////////////////////////
iconPlay::iconPlay(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconPlay::onClick()
{
	pGame->setGameMode(1);
	pGame->getball()->draw();
	pGame->getGameToolbar()->drawPlayMode();
}

////////////////////////////////////////////////////  class iconExit   //////////////////////////////////////////////
iconExit::iconExit(point r_uprleft, int r_width, int r_height, game* r_pGame):
	toolbarIcon(r_uprleft, r_width, r_height,  r_pGame)
{}

void iconExit::onClick()
{
	//TO DO: add code for cleanup and game exit here
}

////////////////////////////////////////////////////  class iconPause   //////////////////////////////////////////////
iconPause::iconPause(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconPause::onClick()
{
	//TO DO: add code for cleanup and game exit here
}


////////////////////////////////////////////////////  class iconContinue   //////////////////////////////////////////////
iconContinue::iconContinue(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconContinue::onClick()
{
	//TO DO: add code for cleanup and game exit here
}


////////////////////////////////////////////////////  class iconStop   //////////////////////////////////////////////
iconStop::iconStop(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconStop::onClick()
{
	pGame->setGameMode(0);
	pGame->reset_game();
	pGame->getGameToolbar()->drawDesignMode();
}




////////////////////////////////////////////////////  class toolbar   //////////////////////////////////////////////
toolbar::toolbar(point r_uprleft, int wdth, int hght, game* pG):
	drawable(r_uprleft, wdth, hght, pG)
{	
	
	height = hght;
	pGame = pG;

	//First prepare List of images for each icon
	//To control the order of these images in the menu, reoder them in enum ICONS above	
	iconsImages[ICON_ADD_NORM] = "images\\ToolbarIcons\\NormalBrickIcon.jpg";
	iconsImages[ICON_ADD_BOMB] = "images\\ToolbarIcons\\BombBrickIcon.jpg";
	iconsImages[ICON_ADD_ROCK] = "images\\ToolbarIcons\\RockBrickIcon.jpg";
	iconsImages[ICON_ADD_POWERUP_DOWN] = "images\\ToolbarIcons\\Powerup_downBrickIcon.jpg";
	iconsImages[ICON_ADD_HARD] = "images\\ToolbarIcons\\hardbrickIcon.jpg";
	iconsImages[ICON_ADD_SWAP] = "images\\ToolbarIcons\\doublebrick.jpg";

	iconsImages[ICON_DELETE] = "images\\ToolbarIcons\\DeleteIcon.jpg";
	iconsImages[ICON_LOAD] = "images\\ToolbarIcons\\LoadIcon.jpg";
	iconsImages[ICON_SAVE] = "images\\ToolbarIcons\\SaveIcon.jpg";
	iconsImages[ICON_PLAY] = "images\\ToolbarIcons\\PlayIcon.jpg";
	iconsImages[ICON_EXIT] = "images\\ToolbarIcons\\ExitIcon.jpg";
	iconsImages[ICON_PAUSE] = "images\\ToolbarIcons\\PauseIcon.jpg";
	iconsImages[ICON_CONTINUE] = "images\\ToolbarIcons\\ContinueIcon.jpg";
	iconsImages[ICON_STOP] = "images\\ToolbarIcons\\StopIcon.jpg";

	point p;
	p.x = 0;
	p.y = 0;

	iconsList = new toolbarIcon* [ICON_COUNT];

	//For each icon in the tool bar
	//	1- Create an object setting its upper left corner, width and height
	iconsList[ICON_ADD_NORM] = new iconAddNormalBrick(p, config.iconWidth, height, pGame);
	p.x+= config.iconWidth;
	iconsList[ICON_ADD_BOMB] = new iconAddBombBrick(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_ADD_ROCK] = new iconAddRockBrick(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_ADD_POWERUP_DOWN] = new iconAddPowerup_downBrick(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_ADD_HARD] = new iconAddhardBrick(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_ADD_SWAP] = new iconAdddoublebrick(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;

	iconsList[ICON_DELETE] = new iconDelete(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_LOAD] = new iconLoad(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_SAVE] = new iconSave(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_PLAY] = new iconPlay(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_EXIT] = new iconExit(p, config.iconWidth, height, pGame);
	p.x =0;
	iconsList[ICON_PAUSE] = new iconPause(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_CONTINUE] = new iconContinue(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_STOP] = new iconStop(p, config.iconWidth, height, pGame);

	//	2-Set its image (from the above images list)
	for (int i = 0; i < ICON_COUNT; i++)
	{
		iconsList[i]->setImageName(iconsImages[i]);

	}
}

toolbar::~toolbar()
{
	for (int i = 0; i < ICON_COUNT; i++)
		delete iconsList[i];
	delete iconsList;
}

void toolbar::drawDesignMode() const
{
	for (int i = 0; i < ICON_COUNT-3; i++)
		iconsList[i]->draw();
	window* pWind = pGame->getWind();
	pWind->SetPen(RED,3);
	pWind->DrawLine(0, height, pWind->GetWidth(), height);

}

void toolbar::drawPlayMode() const
{
	window* pWind = pGame->getWind();
	pWind->SetBrush(PURPLE);
	pWind->DrawRectangle(0, 0, config.windWidth, config.toolBarHeight);
	for (int i = ICON_COUNT - 3; i < ICON_COUNT; i++)
		iconsList[i]->draw();
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, height, pWind->GetWidth(), height);


	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->SetPen(BLACK);

	// Draw score
	pWind->DrawString(900, 5, "Score: " + to_string(pGame->getScore()));

	// Draw timer
	pWind->SetBrush(PURPLE);
	pWind->DrawRectangle(250, 0, 400, config.toolBarHeight);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->SetPen(BLACK);
	//pWind->DrawString(250, 5, "Timer: ");
	
	//Draw hearts for lives
	int heart_side = 30;
	for (int i = 0; i < 3 - lives; i++) {
		pWind->DrawImage("images\\ToolbarIcons\\EmptyHeart.jpg", 520 + heart_side * i, 5, heart_side, heart_side);
	}
	for (int i = 3 - lives; i < 3; i++) {
		pWind->DrawImage("images\\ToolbarIcons\\FullHeart.jpg", 520 + heart_side * i, 5, heart_side, heart_side);
	}
}
void toolbar::draw_time(window* pwind)  {
	times.update_time();
	pwind->SetBrush(PURPLE);
	pwind->DrawRectangle(250, 0, 400, config.toolBarHeight);
	pwind->SetFont(20, BOLD, BY_NAME, "Arial");
	pwind->SetPen(BLACK);
	pwind->DrawString(250, 5, "Timer: " + to_string(times.get_time()));
}

//handles clicks on toolbar icons, returns true if exit is clicked
bool toolbar::handleClickDesignMode(int x, int y) 
{
	if (x > (ICON_COUNT-3) * config.iconWidth)	//click outside toolbar boundaries
		return false;
	
	
	//Check whick icon was clicked
	//==> This assumes that menu icons are lined up horizontally <==
	//Divide x coord of the point clicked by the icon width (int division)
	//if division result is 0 ==> first icon is clicked, if 1 ==> 2nd icon and so on

	int clickedIconIndex = (x / config.iconWidth);
	iconsList[clickedIconIndex]->onClick();	//execute onClick action of clicked icon

	if (clickedIconIndex == ICON_EXIT) return true;	
	if (clickedIconIndex == ICON_PLAY) times.set_time();
	
	return false;


}

bool toolbar::handleClickPlayMode(int x, int y) 
{
	if (x > 3 * config.iconWidth)	//click outside toolbar boundaries
		return false;


	//Check whick icon was clicked
	//==> This assumes that menu icons are lined up horizontally <==
	//Divide x coord of the point clicked by the icon width (int division)
	//if division result is 0 ==> first icon is clicked, if 1 ==> 2nd icon and so on

	int clickedIconIndex = (x / config.iconWidth);
	iconsList[clickedIconIndex+(ICON_COUNT-3)]->onClick();	//execute onClick action of clicked icon

	//if (clickedIconIndex == 2) return true;


	return false;


}

void toolbar::decrease_lives()
{
	if (lives>0) lives--;

	if (lives <= 0) pGame->setGameMode(2);
}

void toolbar::reset_lives()
{
	lives = 3;
}

void toolbar::draw_score()
{
	pGame->getWind()->SetBrush(PURPLE);
	pGame->getWind()->DrawRectangle(900, 0, config.windWidth, config.toolBarHeight);
	pGame->getWind()->SetFont(20, BOLD, BY_NAME, "Arial");
	pGame->getWind()->SetPen(BLACK);
	pGame->getWind()->DrawString(900, 5, "Score: " + to_string(pGame->getScore()));
}


#pragma once

//This file contains all classes related to toolbar (toolbar icon classes & toolbar class itself)
#include "drawable.h"
#include "timer.h"

////////////////////////////////////////////////////  class toolbarIcon   ////////////////////////////////////////////////////
//Base class for all toolbar icons 
class toolbarIcon :public drawable
{
public:
	toolbarIcon(point r_uprleft, int r_width, int r_height, game* r_pGame);
    virtual void onClick()=0;   //The action that should be taken when this icon is clicked
};

////////////////////////////////////////////////////  class iconAddNormalBrick   //////////////////////////////////////////////
class iconAddNormalBrick :public toolbarIcon
{
public:
	iconAddNormalBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};

////////////////////////////////////////////////////  class iconAddBombBrick   //////////////////////////////////////////////
class iconAddBombBrick :public toolbarIcon
{
public:
	iconAddBombBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};

////////////////////////////////////////////////////  class iconAddRockBrick   //////////////////////////////////////////////
class iconAddRockBrick :public toolbarIcon
{
public:
	iconAddRockBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};

////////////////////////////////////////////////////  class iconAddPowerup_downBrick   //////////////////////////////////////////////
class iconAddPowerup_downBrick :public toolbarIcon
{
public:
	iconAddPowerup_downBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};
////////////////////////////////////////////////////  class iconAddHardBrick   //////////////////////////////////////////////

class iconAddhardBrick :public toolbarIcon
{
public:
	iconAddhardBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};
////////////////////////////////////////////////////////////////////////////

class iconAdddoublebrick :public toolbarIcon
{
public:
	iconAdddoublebrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};


////////////////////////////////////////////////////  class iconDelete   //////////////////////////////////////////////
class iconDelete :public toolbarIcon
{
public:
	iconDelete(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};

////////////////////////////////////////////////////  class iconLoad   //////////////////////////////////////////////
class iconLoad :public toolbarIcon
{
public:
	iconLoad(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};

////////////////////////////////////////////////////  class iconSave   //////////////////////////////////////////////
class iconSave :public toolbarIcon
{
public:
	iconSave(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};

////////////////////////////////////////////////////  class iconPlay   //////////////////////////////////////////////
class iconPlay :public toolbarIcon
{
public:
	iconPlay(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};

////////////////////////////////////////////////////  class iconExit   //////////////////////////////////////////////
class iconExit :public toolbarIcon
{
public:
	iconExit(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};


////////////////////////////////////////////////////  class iconPause   //////////////////////////////////////////////
class iconPause :public toolbarIcon
{
public:
	iconPause(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};


////////////////////////////////////////////////////  class iconContinue   //////////////////////////////////////////////
class iconContinue :public toolbarIcon
{
public:
	iconContinue(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};


////////////////////////////////////////////////////  class iconStop   //////////////////////////////////////////////
class iconStop :public toolbarIcon
{
public:
	iconStop(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};

////////////////////////////////////////////////////  class toolbar   //////////////////////////////////////////////
class toolbar:public drawable
{

	enum ICONS //The icons of the toolbar (you should add more icons)
	{
		//Note: Icons are ordered here as they appear in menu
		//If you want to change the menu icons order, change the order here
		ICON_ADD_NORM,		//add normal brick

		ICON_ADD_BOMB,

		ICON_ADD_ROCK,

		ICON_ADD_POWERUP_DOWN,

		ICON_ADD_HARD,

		ICON_ADD_SWAP,

		//TODO: Add more icons names here

		ICON_DELETE,

		ICON_LOAD,

		ICON_SAVE,

		ICON_PLAY,

		ICON_EXIT,		//Exit icon

		ICON_PAUSE,		

		ICON_CONTINUE,

		ICON_STOP,

		ICON_COUNT		//no. of menu icons ==> This should be the last line in this enum

	};

private:
    toolbarIcon** iconsList; //an array of toolbarIcon pointers
	string iconsImages[ICON_COUNT];
	game* pGame;
	
public:
	toolbar(point r_uprleft, int r_width, int r_height, game* r_pGame);
	~toolbar();
    void drawDesignMode() const;
	void drawPlayMode() const;
	void draw_time(window* pwind);
	bool handleClickDesignMode(int x, int y);	//handles clicks on toolbar icons, returns true if exit is clicked
	bool handleClickPlayMode(int x, int y);
	timer times;
	int lives = 3;
	void decrease_lives();
	void reset_lives();
	void draw_score();
};


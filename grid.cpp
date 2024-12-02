#include "grid.h"
#include "game.h"
#include "gameConfig.h"
#include <fstream>
#include"Bricks.h"
class swapBrick;

grid::grid(point r_uprleft, int wdth, int hght, game* pG):
	drawable(r_uprleft, wdth, hght, pG)
{

	rows = height / config.brickHeight;
	cols = width / config.brickWidth;

	brickMatrix = new brick ** [rows];
	for (int i = 0; i < rows; i++)
		brickMatrix[i] = new brick * [cols];

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			brickMatrix[i][j] = nullptr;
}

grid::~grid()
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (brickMatrix[i][j])
				delete brickMatrix[i][j];	

	for (int i = 0; i < rows; i++)
		delete brickMatrix[i];

	delete brickMatrix;

}
brick*** grid::get_matrix() {
	return brickMatrix;
}

int grid::get_rows() const
{
	return rows;
}

int grid::get_cols() const
{
	return cols;
}

void grid::draw() const
{
	window* pWind = pGame->getWind();
	//draw lines showing the grid
	pWind->SetPen(config.gridLinesColor,1);
	pWind->SetBrush(LAVENDER);

	//draw horizontal lines
	for (int i = 0; i < rows; i++) {
		int y = uprLft.y + (i + 1) * config.brickHeight;
		pWind->DrawLine(0, y, width, y);
	}
	//draw vertical lines
	for (int i = 0; i < cols; i++) {
		int x = (i + 1) * config.brickWidth;
		pWind->DrawLine(x, uprLft.y, x, uprLft.y+ rows* config.brickHeight);
	}

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (brickMatrix[i][j])
				brickMatrix[i][j]->draw();	//draw exisiting bricks


}

int grid::addBrick(BrickType brkType, point clickedPoint)
{
	//TODO:
	// 1- Check that the clickedPoint is within grid range (and return -1)
	// 2- Check that the clickedPoint doesnot overlap with an exisiting brick (return 0)

	//Here we assume that the above checks are passed
	
	//From the clicked point, find out the index (row,col) of the corrsponding cell in the grid
	int gridCellRowIndex = (clickedPoint.y-uprLft.y) / config.brickHeight;
	int gridCellColIndex = clickedPoint.x / config.brickWidth;

	//Now, align the upper left corner of the new brick with the corner of the clicked grid cell
	point newBrickUpleft;
	newBrickUpleft.x = uprLft.x + gridCellColIndex * config.brickWidth;
	newBrickUpleft.y = uprLft.y+ gridCellRowIndex * config.brickHeight;

	switch (brkType)
	{
	case BRK_NRM:	//The new brick to add is Normal Brick
		brickMatrix[gridCellRowIndex][gridCellColIndex] = new normalBrick(newBrickUpleft, config.brickWidth, config.brickHeight, pGame);
		break;

	case BRK_BMB:
		brickMatrix[gridCellRowIndex][gridCellColIndex] = new bombBrick(newBrickUpleft, config.brickWidth, config.brickHeight, pGame);
		break;

	case BRK_RCK:
		brickMatrix[gridCellRowIndex][gridCellColIndex] = new rockBrick(newBrickUpleft, config.brickWidth, config.brickHeight, pGame);
		break;

	case BRK_PUD:
		brickMatrix[gridCellRowIndex][gridCellColIndex] = new powerup_downBrick(newBrickUpleft, config.brickWidth, config.brickHeight, pGame);
		break;

	case BRK_HRD:
		brickMatrix[gridCellRowIndex][gridCellColIndex] = new hardBrick(newBrickUpleft, config.brickWidth, config.brickHeight, pGame);
      break;

	case BRK_DB:
		brickMatrix[gridCellRowIndex][gridCellColIndex] = new doubleBrick(newBrickUpleft, config.brickWidth, config.brickHeight, pGame);
		break;
		//TODO: 
		// handle more types
	}
	return 1;
}

void grid::sortDangling(point brickPosition)
{
	int col = (brickPosition.x) / config.brickWidth;
	int row = (brickPosition.y - config.toolBarHeight) / config.brickHeight;
	brickMatrix[row][col] = nullptr;
}

void grid::deleteBrick(point brickPosition)
{
	pGame->getWind()->SetBrush(LAVENDER);
	pGame->getWind()->SetPen(LAVENDER);
	pGame->getWind()->SetPen(config.gridLinesColor, 1);
	pGame->getWind()->DrawRectangle(brickPosition.x, brickPosition.y, brickPosition.x + 60, brickPosition.y + 30);
	pGame->getWind()->DrawLine(brickPosition.x, brickPosition.y, brickPosition.x + 60, brickPosition.y);
	pGame->getWind()->DrawLine(brickPosition.x, brickPosition.y, brickPosition.x, brickPosition.y + 30);
	pGame->getWind()->DrawLine(brickPosition.x + 60, brickPosition.y, brickPosition.x + 60, brickPosition.y + 30);
	pGame->getWind()->DrawLine(brickPosition.x, brickPosition.y + 30, brickPosition.x + 60, brickPosition.y + 30);
	int col = (brickPosition.x) / config.brickWidth;
	int row = (brickPosition.y - config.toolBarHeight) / config.brickHeight;
	if (brickMatrix[row][col]) {
		delete brickMatrix[row][col];
		brickMatrix[row][col] = nullptr;

	}
}

bool grid::saveToFile(string filename) const
{
	fstream outFile("IO files\\" + filename + ".txt", ios::out);
	for (int i = 0; i < get_rows(); i++) {
		for (int j = 0; j < get_cols(); j++) {
			if (brickMatrix[i][j]) {
				outFile << i << " " << j << " \t" << (int)brickMatrix[i][j]->getType() << endl;
			}
		}
	}
	outFile.close();
	return true;
}

bool grid::loadFromFile(string filename)
{
	fstream inFile("IO files\\" + filename + ".txt", ios::in);
	if (!inFile)
	{
		pGame->printMessage("File doesn't exist!");
		inFile.close();
		return false;
	}

	//Clear Matrix first
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (brickMatrix[i][j]) {
				delete brickMatrix[i][j];	//delete all allocated bricks
				brickMatrix[i][j] = nullptr;
			}

	//Load new
	int row, column, brickType;
	point brickpos;
	while (inFile >> row) {
		inFile >> column;
		inFile >> brickType;
		brickpos.x = column * config.brickWidth;
		brickpos.y = row * config.brickHeight + uprLft.y;
		addBrick((BrickType)brickType, brickpos);
	}
	draw();
	inFile.close();
	return true;
}

void grid::swapBrick(point brickPosition1, point brickPosition2)
{
	int row1 = (brickPosition1.y - config.toolBarHeight) / config.brickHeight;
	int col1 = brickPosition1.x / config.brickWidth;
	int row2 = (brickPosition2.y - config.toolBarHeight) / config.brickHeight;
	int col2 = brickPosition2.x / config.brickWidth;

	if (row1 >= 0 && row1 < rows && col1 >= 0 && col1 < cols &&
		row2 >= 0 && row2 <rows && col2 >= 0 && col2 < cols) {
		std::swap(brickMatrix[row1][col1], brickMatrix[row2][col2]);

		if (brickMatrix[row1][col1])
			brickMatrix[row1][col1]->setposition(brickPosition1);

		if (brickMatrix[row2][col2])
			brickMatrix[row2][col2]->setposition(brickPosition2);
	}
}


void grid::draw_lines()
{
	window* pWind = pGame->getWind();
	//draw lines showing the grid
	pWind->SetPen(config.gridLinesColor, 1);
	pWind->SetBrush(LAVENDER);
	for (int i = 0; i < rows; i++) {
		int y = uprLft.y + (i + 1) * config.brickHeight;
		pWind->DrawLine(0, y, width, y);
	}
	//draw vertical lines
	for (int i = 0; i < cols; i++) {
		int x = (i + 1) * config.brickWidth;
		pWind->DrawLine(x, uprLft.y, x, uprLft.y + rows * config.brickHeight);
	}
}

void grid::checkBrickDestruction() {
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (brickMatrix[i][j]) {
				return;
			}
	pGame->setGameMode(2);
	pGame->setWinStatus(true);
}
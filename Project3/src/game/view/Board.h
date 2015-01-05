#pragma once
#include "../../scenegraph/Node.h"
#include "../view/BoardPiece.h"
#include "../controller/MatchController.h"
#include <iostream>
#include "../model/Move.h"
#include "AngleChooser.h"
#include "Cube.h"


class AngleChooser;
class BoardPiece;
class MatchController;
class Board;

class BackButton: public Node
{
private:
	Board * board;
public:
	BackButton(Board * board);
	bool clickHandler();

};


class BoardHouse: public Node
{
private:
	int i, j;
	Board * board;
public:
	
	BoardHouse(Board * board, int i, int j);
	bool clickHandler();
	void setEnabled(bool val);
};


class Board: public Node
{
public:
	MatchController * controller;
	BoardPiece * boardPieces[6][10];
	BoardHouse * boardHouses[6][10];
	AngleChooser * angleChooser;
	Cube * leftScore,  * rightScore;
	float cellSize, outPadding, innerPadding;
	void coordsConvert(int i, int j, float &  xx, float & zz);
public:
	Node * modelPiece;

	Board();
	BoardPiece * addPiece(int i, int j);
	BoardPiece *& piece(int i, int j);
	BoardHouse *& house(int i, int j);

	void getCoords(BoardPiece * piece, int & i, int & j);

	int pushUpPiece(int delay,int i,int j);
	int pullDownPiece(int delay, int i,int j);
	int slidePiece(int delay, int fromI,int fromJ, int toI, int toJ);
	int rotatePiece(int delay, int fromI,int fromJ, int rot);
	void moveAngleChooserTo(int i, int j);

	AngleChooser * getAngleChooser();

	MatchController * getController();
	void setController(MatchController * controller);

	void setSelectable(std::vector<IJ> pieces);
	void setSelectableHouses(std::vector<IJ> houses);
	void unsetSelectableAll();
	void unsetSelectableAllHouses();

	std::vector<IJ> getOutsidePieces(int player);
	std::vector<IJ> getOutsideFreeHouses(int player);

	virtual void update(unsigned time);

	
};


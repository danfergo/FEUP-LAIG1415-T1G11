#pragma once

#include "../../scenegraph/Node.h"
#include "Board.h"

#include <iostream>

class Board;

class BoardPiece: public Node
{
private:
	int angle;
	Board * board;
	
	
public:
	Node * inner;
	BoardPiece(Board * board);
	void animationCallback();
	int getAngle();
	void setAngle(int angle);
	void rotAngle(int angle);
	virtual bool clickHandler();
};


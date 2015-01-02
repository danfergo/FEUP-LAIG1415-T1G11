#pragma once
#include "../../scenegraph/Node.h"
#include "../view/BoardPiece.h"
#include "../controller/MatchController.h"

#include <iostream>

class Board: public Node
{
private:
	BoardPiece * boardPieces[6][8];
	Node * boardHousesBtns[6][8];
	Node * anglePositionBtnGroup;
	MatchController * controler;
public:
	Board(void);
	
	void addPiece(int i, int j, int color);
	void setRotationGostAt(int i, int j, int angPos);
	void setHouseSelectable(int i, int j);
	void setPieceSelectable(int i, int j, int angPos);


	void slidePiece(int delay, int fromI,int fromJ, int toI, int toJ);
	void rotatePiece(int delay, int fromI,int fromJ, int angPos);
	void pushUpPiece(int delay, int i,int j);
	void pullDownPiece(int delay, int i,int j);

	virtual bool clickHandler(){
		std::cout << "board " << std::endl;
		return false;
	}

};


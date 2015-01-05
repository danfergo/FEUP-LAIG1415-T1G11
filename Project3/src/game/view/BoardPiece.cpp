#include "BoardPiece.h"

#include "../../scenegraph/primitives/Retangle.h"

#include "ConcaveCube.h"

BoardPiece::BoardPiece(Board * board): angle(0), board(board)
{
	inner = new Node(board->modelPiece);
	inner->addScaling(0.05,0.05,0.05);
	this->addDescendants(inner);
	
}


void BoardPiece::animationCallback(){
	this->board->getController()->animationEnded();
}


int BoardPiece::getAngle(){
	return this->angle;
}

void BoardPiece::setAngle(int angle){
	this->angle = angle%8;
}

void BoardPiece::rotAngle(int angle){
	this->angle = (this->angle+angle)%8;
}


bool BoardPiece::clickHandler(){
	int i, j;
	this->board->getCoords(this,i,j);
	this->board->getController()->selectBoardCoords(i,j);
	return true;
}
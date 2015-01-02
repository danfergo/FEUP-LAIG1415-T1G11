#include "Board.h"
#include "BoardPiece.h"

Board::Board(void)
{
	Node * node = new BoardPiece();
	node->setTouchable(true);
	this->addDescendants(node);
	this->setTouchable(true);
}



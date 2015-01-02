#include "BoardPiece.h"

#include "../../scenegraph/primitives/Retangle.h"
#include "ConcaveCube.h"

BoardPiece::BoardPiece(void)
{
	Point2d vertexes[2] = {{-1,-1}, {1,1}};
	this->addPrimitive(new ConcaveCube());
}



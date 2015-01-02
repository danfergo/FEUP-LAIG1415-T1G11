#pragma once

#include "../../scenegraph/Node.h"


#include <iostream>

class BoardPiece: public Node
{

public:
	BoardPiece(void);

	virtual bool clickHandler(){
		std::cout << "board piece " << std::endl;
		return false;
	}
};


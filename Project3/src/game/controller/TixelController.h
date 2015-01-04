#pragma once
#include "CGFapplication.h"

#include "../../scenegraph/parser/ANFparser.h"
#include "../../scenegraph/Interface.h"
#include "../../game/view/Board.h"
#include "MatchController.h"

class TixelController: public CGFapplication
{
private:
	MatchController * matchController;
public:
	TixelController(void);
	void init(int argc, char* argv[]);
	~TixelController(void);
};


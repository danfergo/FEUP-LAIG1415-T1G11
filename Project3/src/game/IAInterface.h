#pragma once
#include "Connection.h"
#include "model/GameState.h"
#include <vector>
#include "model/Move.h"

#define BUFFER_MAX_SIZE		1024

class IAInterface
{
private:
	char temporaryBuffer[BUFFER_MAX_SIZE];
	Connection conn;
	
public:
	static enum Mode {PlayerVsPlayer};
	IAInterface(void);
	GameState * initialize(enum Mode mode);
	std::vector<IJ> availablePiecesToMove(GameState * gamestate);
	std::vector<IJ> availableMoves(GameState * gamestate, IJ coords);
	std::vector<int> availableAngles(GameState * gamestate, IJ from, IJ to);	
	GameState * chooseMove(Mode * move);
	GameState * makeMove(Mode * move);
};


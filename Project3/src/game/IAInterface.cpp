#include "IAInterface.h"


#include <sstream>



IAInterface::IAInterface(void): conn(BUFFER_MAX_SIZE) {
	
}

GameState * IAInterface::initialize(enum Mode mode){
	std::stringstream cmd;
	cmd << "initialize(" << (int)mode << ").\n";

	conn.send(cmd.str().c_str());
	conn.receive(temporaryBuffer);
	
	return new GameState(temporaryBuffer);
}

std::vector<IJ> IAInterface::availablePiecesToMove(GameState * gamestate){
	std::vector<IJ> coords;

	conn.send(std::string("available_pieces(" + gamestate->toString() + ").\n").c_str());
	conn.receive(temporaryBuffer);

	return coords;
}
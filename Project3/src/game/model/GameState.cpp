#include "GameState.h"
#include <iostream>
#include "../IAInterface.h"

GameState::GameState(const char * state): state(state)

{
}
GameState::GameState(std::string state): state(state)
{
}
	
int GameState::currentPlayer(){
	std::vector<std::string>  completeGameState, gameState;
	IAInterface::parseListStrings(state.c_str(),completeGameState);
	
	IAInterface::parseListStrings(completeGameState[2].c_str(),gameState);

	return atoi(gameState[1].c_str());
}


std::string GameState::toString(){
	return state;
}
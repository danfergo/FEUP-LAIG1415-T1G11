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
bool GameState::getHouseAngle(int i, int j, int & a){
	std::vector<std::string>  completeGameState, gameState, gameboard, line,cell;
	IAInterface::parseListStrings(state.c_str(),completeGameState);
	IAInterface::parseListStrings(completeGameState[2].c_str(),gameState);
	IAInterface::parseListStrings(gameState[0].c_str(),gameboard);
	IAInterface::parseListStrings(gameboard[i].c_str(),line);
	IAInterface::parseListStrings(line[j].c_str(),cell);
	if(cell.size() == 0){
		return false;
	}
	a = atoi(cell[1].c_str());
	return true;
};

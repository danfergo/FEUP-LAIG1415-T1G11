#include "GameState.h"
#include <iostream>

GameState::GameState(const char * state): state(state)

{
}
GameState::GameState(std::string state): state(state)
{
}
	

std::string GameState::toString(){
	return state;
}
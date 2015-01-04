#pragma once
#include <string>

class GameState
{
private:
	std::string state;
public:
	enum Playing {PersonPlaying, ComputerPlaying};
	GameState(const char * state);
	GameState(std::string state);
	enum Playing whoIsPlaying();
	bool hasExtraMove();
	bool gameIsOver();
	int result();
	int currentPlayer();
	std::string toString();
};


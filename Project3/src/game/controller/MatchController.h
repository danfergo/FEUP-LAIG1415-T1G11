#pragma once
#include "../IAInterface.h"
#include "MatchController.h"

class MatchController
{
private:
	IAInterface iaInterface;
	enum PState {ChoosingPiece, ChoosingWhereToGo, ChoosingEndAngle};
	bool waiting;
	std::vector<GameState *> game;
	enum PState playingState;
public:
	MatchController(void);
	void update();

	void switchToChoosingPiece();

	/** Notifications receivers **/
	void selectedBoardPiece(int i, int j);
	void selectedBoardHouse(int i, int j);
	void selectedAnglePosition(int anglePosition);
	void animationEnded();
	void refresh();
};


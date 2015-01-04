#pragma once
#include "../IAInterface.h"
#include "../view/Board.h"

class Board;
class MatchController
{
private:
	IAInterface iaInterface;
	enum PState {ChoosingPiece, ChoosingWhereToGo, ChoosingAngle};
	Board * board;
	std::vector<GameState *> gameStates;
	enum PState playingState;
	IJ curStart, curEnd;
	int curAngle;
public:
	MatchController(Board * board);
	void update();

	/**  **/
	void play();
	void pcPlay();
	void playerPlay();
	void makeMove();
	void setControlsChooseEnd();
	void setControlsChooseAngle();


	/** Notifications receivers **/
	void selectBoardCoords(int i, int j);
	void selectAngle(int angle);
	void animationEnded();
	
	void setBoard(Board * board);  
};


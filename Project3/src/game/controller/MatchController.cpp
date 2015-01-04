#include "MatchController.h"


MatchController::MatchController(Board * board): iaInterface()
{
	this->board = board;
	gameStates.push_back(iaInterface.initialize(IAInterface::PlayerVsPlayer));

	for(int i = 0; i < 5; i++){
		this->board->addPiece(i,-2);
		this->board->addPiece(i,-1);
		this->board->addPiece(i,6);
		this->board->addPiece(i,7);
	}
	this->playerPlay();
}



void MatchController::setBoard(Board * board){
	this->board = board;
}

void MatchController::animationEnded(){
	switch(playingState){
		case ChoosingWhereToGo:
			setControlsChooseEnd();
			break;
		case ChoosingAngle:
			setControlsChooseAngle();
			break;
	}
}


void MatchController::play(){
	if(iaInterface.isHumanPlaying(gameStates.back())) {
		playerPlay();
	}else{
		pcPlay();
	}
}

void MatchController::pcPlay(){
	
}

void MatchController::playerPlay(){

	std::vector<IJ> coords = this->iaInterface.availablePiecesToMove(gameStates.back());
	std::vector<IJ> outCoords = this->board->getOutsidePieces(gameStates.back()->currentPlayer());
	coords.insert(coords.begin(), outCoords.begin(), outCoords.end());
	board->setSelectable(coords);
	std::cout << "--ll------" << coords.size() << std::endl;
	
	playingState = ChoosingPiece;
}

void MatchController::makeMove(){
	Move * move = new Move();
	move->from = curStart;
	move->from = curEnd;
	move->toA = curAngle;
	gameStates.push_back(this->iaInterface.makeMove(gameStates.back(),move));

	play();
}

void MatchController::setControlsChooseEnd(){
	std::vector<IJ> coords = this->iaInterface.availableMoves(gameStates.back(),curStart);
	
	if(!curStart.isOutOfBoard()){
		std::vector<IJ> outCoords = this->board->getOutsidePieces(gameStates.back()->currentPlayer());
		coords.insert(coords.begin(), outCoords.begin(), outCoords.end()); 
	}
	
	
	this->board->setSelectableHouses(coords);
}

void MatchController::setControlsChooseAngle(){
	std::vector<int> angles = this->iaInterface.availableAngles(gameStates.back(),curStart,curEnd);

	this->board->moveAngleChooserTo(curEnd.i,curEnd.j);
	this->board->getAngleChooser()->enable(angles);
}

void MatchController::selectBoardCoords(int i, int j){
	board->unsetSelectableAll();
	board->unsetSelectableAllHouses();
	board->getAngleChooser()->disableAll();

	int delay;

	switch(playingState){
		case ChoosingPiece:
			this->curStart.set(i,j);
			this->board->pushUpPiece(0,curStart.i,curStart.j);
			playingState = ChoosingWhereToGo;
			break;
		case ChoosingWhereToGo:
			this->curEnd.set(i,j);
			if(curStart.i == curEnd.i && curStart.j == curEnd.j){
				
			}if(!curEnd.isOutOfBoard() && !curStart.isOutOfBoard()){
				delay = board->pullDownPiece(0,curStart.i,curStart.j);
				delay += board->slidePiece(delay,curStart.i,curStart.j, curEnd.i,curEnd.j);
				this->board->pushUpPiece(delay,curEnd.i,curEnd.j);
			} else{
				delay = board->slidePiece(0,curStart.i,curStart.j, curEnd.i,curEnd.j);
				board->pullDownPiece(delay,curEnd.i,curEnd.j);
				this->board->pushUpPiece(delay,curEnd.i,curEnd.j);
			}


			
			if(curEnd.isOutOfBoard()){
				
			}else{
				playingState = ChoosingAngle;
			}
			break;
	}
	
	std::cout << "Selected coords (" << i << "," << j << ")" << std::endl;
}
void MatchController::selectAngle(int angle){
	std::cout << "Selected angle " << angle << std::endl;
	board->getAngleChooser()->disableAll();
	this->curAngle = angle;
	switch(playingState){
		case ChoosingAngle:
			board->pullDownPiece(0,curEnd.i,curEnd.j);
			board->rotatePiece(0,curEnd.i, curEnd.j,curAngle);
			makeMove();
			break;
	}
}
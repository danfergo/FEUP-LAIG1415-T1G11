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
	this->board->unsetSelectableAll();
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
	currentMove = new Move();
	playingState = ChoosingPiece;
}

void MatchController::makeMove(){

	gameStates.push_back(this->iaInterface.makeMove(gameStates.back(),currentMove));

	play();
}

void MatchController::setControlsChooseEnd(){
	std::vector<IJ> coords = this->iaInterface.availableMoves(gameStates.back(),this->currentMove->from);
	
	if(!this->currentMove->from.isOutOfBoard()){
		std::vector<IJ> outCoords = this->board->getOutsidePieces(gameStates.back()->currentPlayer());
		coords.insert(coords.begin(), outCoords.begin(), outCoords.end()); 
	}
	
	this->board->setSelectableHouses(coords);
}

void MatchController::setControlsChooseAngle(){
	std::vector<int> angles = this->iaInterface.availableAngles(gameStates.back(),this->currentMove->from,this->currentMove->to);

	this->board->moveAngleChooserTo(this->currentMove->to.i,this->currentMove->to.j);
	this->board->getAngleChooser()->enable(angles);
}

void MatchController::selectBoardCoords(int i, int j){
	board->unsetSelectableAll();
	board->unsetSelectableAllHouses();
	board->getAngleChooser()->disableAll();

	int delay;

	switch(playingState){
		case ChoosingPiece:
			this->currentMove->fromA = board->piece(i,j)->getAngle();
			this->currentMove->from.set(i,j);
			this->board->pushUpPiece(0,this->currentMove->from.i,this->currentMove->from.j);
			playingState = ChoosingWhereToGo;
			break;
		case ChoosingWhereToGo:
			this->currentMove->to.set(i,j);
			if(this->currentMove->from.i == this->currentMove->to.i && this->currentMove->from.j == this->currentMove->to.j){
				// keep in the same position
			}if(!this->currentMove->to.isOutOfBoard() && !this->currentMove->from.isOutOfBoard()){
				delay = board->pullDownPiece(0,this->currentMove->from.i,this->currentMove->from.j);
				delay += board->slidePiece(delay,this->currentMove->from.i,this->currentMove->from.j, this->currentMove->to.i,this->currentMove->to.j); 
				this->board->pushUpPiece(delay,this->currentMove->to.i,this->currentMove->to.j);
			} else{
				delay = board->slidePiece(0,this->currentMove->from.i,this->currentMove->from.j, this->currentMove->to.i,this->currentMove->to.j);
				board->pullDownPiece(delay,this->currentMove->to.i,this->currentMove->to.j);
				this->board->pushUpPiece(delay,this->currentMove->to.i,this->currentMove->to.j);
			}


			
			if(this->currentMove->to.isOutOfBoard()){
				// we dont need a final angle. skip that.
				makeMove();
			}else{
				playingState = ChoosingAngle;
			}
			break;
	}
	
}
void MatchController::selectAngle(int angle){
	board->getAngleChooser()->disableAll();

	this->currentMove->toA = angle;
	switch(playingState){
		case ChoosingAngle:
			board->pullDownPiece(0,this->currentMove->to.i,this->currentMove->to.j);
			board->rotatePiece(0,this->currentMove->to.i, this->currentMove->to.j,this->currentMove->toA);
			makeMove();
			break;
	}
}

void MatchController::goBack(){


}
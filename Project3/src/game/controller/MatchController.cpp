#include "MatchController.h"


MatchController::MatchController(void): iaInterface()
{
	GameState * gs = iaInterface.initialize(IAInterface::PlayerVsPlayer);
	iaInterface.availablePiecesToMove(gs);

	
}

void MatchController::refresh(){
	if(waiting){
		return;
	}


	switch(playingState){
		case ChoosingPiece:
			break;
		
	}



}

void MatchController::update(){

}
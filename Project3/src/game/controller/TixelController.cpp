#include "TixelController.h"
#include "../view/GameCamera.h"

TixelController::TixelController(void):CGFapplication(), currentState(ChoosingMode)
{
	scenes[0].scene = new Scene(); scenes[0].board = NULL;
	scenes[1].scene = new Scene(); scenes[1].board = NULL;
	
	menuMode = new Scene();
	menuScenario = new Scene();
}


TixelController::~TixelController(void)
{

}


void TixelController::init(int argc, char* argv[]){

	CGFapplication::init(&argc,argv);

	ANFparser parser = ANFparser(0);
	
	
	if(!parser.parse(menuMode,"resources/scenes/mode.menu")) throw ParseExep();
	ANFparser::buttonFound0->setController(this);
	ANFparser::buttonFound1->setController(this);
	ANFparser::buttonFound2->setController(this);
	ANFparser::buttonFound3->setController(this);

	if(!parser.parse(menuScenario,"resources/scenes/world.menu")) throw ParseExep();
	ANFparser::buttonFound0->setController(this);
	ANFparser::buttonFound1->setController(this);

	if(!parser.parse(scenes[0].scene,"resources/scenes/nature.world")) throw ParseExep();
	scenes[0].board = ANFparser::boardFound;
	scenes[0].board->modelPiece = ANFparser::pieceModelFound;

	if(!parser.parse(scenes[1].scene,"resources/scenes/lardlad.world")) throw ParseExep();
	scenes[1].board = ANFparser::boardFound;	
	scenes[1].board->modelPiece = ANFparser::pieceModelFound;

	this->scenes[1].board->setController(new MatchController(this->scenes[1].board));

	intrface = new Interface();


	CGFapplication::setScene(menuMode); 
	CGFapplication::setInterface(intrface); 






	/**
	
	((GameCamera *)lardLadWorld->getTheActiveCamera())->produceRotation(180,20);  
	**/

}


void TixelController::selectButton(int i){
	

	switch(currentState){
	case ChoosingMode:
		this->mode = i;
		intrface->setScene(menuScenario);
		CGFapplication::setScene(menuScenario); 
		currentState = ChoosingScenario;
		break;
	case ChoosingScenario:
		CGFapplication::setScene(this->scenes[i].scene);
		intrface->setScene(this->scenes[i].scene);
		
		
/**
		this->scenes[i].board->setController(new MatchController(this->scenes[i].board));
		**/
		currentState = Playing;
		break;
	}
}



#include "TixelController.h"
#include "../view/GameCamera.h"

TixelController::TixelController(void):CGFapplication()
{




}


TixelController::~TixelController(void)
{
}


void TixelController::init(int argc, char* argv[]){

	CGFapplication::init(&argc,argv);

	Scene * natureWorld = new Scene();
	Scene * lardLadWorld = new Scene();
	
	


	
	ANFparser parser = ANFparser(0);
	if(parser.parse(natureWorld,"resources/scenes/nature.world")){
			
		if(parser.parse(lardLadWorld,"resources/scenes/lardlad.world")){
		
			CGFapplication::setScene(lardLadWorld);
		}

		CGFapplication::setScene(natureWorld);
		CGFapplication::setInterface(new Interface()); 
	}
	
	ANFparser::boardFound->setController(new MatchController(ANFparser::boardFound));
		 

	 ((GameCamera *)natureWorld->getTheActiveCamera())->produceRotation(180,10); 
}




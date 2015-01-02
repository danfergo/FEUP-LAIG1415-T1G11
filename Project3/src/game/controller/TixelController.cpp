#include "TixelController.h"


TixelController::TixelController(void):CGFapplication(), matchController()
{




}


TixelController::~TixelController(void)
{
}


void TixelController::init(int argc, char* argv[]){

	CGFapplication::init(&argc,argv);

	Scene * s = new TixelScene();
	s->setRoot(new Board());
	
	CGFapplication::setScene(s);
	CGFapplication::setInterface(new Interface());
}
void TixelController::update(){
	this->matchController.update();
}
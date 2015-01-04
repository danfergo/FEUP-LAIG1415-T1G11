#include "AngleChooser.h"

#include "../../scenegraph/primitives/Triangle.h"
#include "../controller/MatchController.h"


AngleChooserBtn::AngleChooserBtn(AngleChooser * chooser,int angle): chooser(chooser), angle(angle){
	Point3d points[3] = {{1,0,0},{0,0,-1},{-1,0,0}};
	this->addPrimitive(new Triangle(points));
	this->addRotationY(-45*angle);
	this->addTranslation(0, 0,-4);
}

bool AngleChooserBtn::clickHandler(){
	this->chooser->getBoard()->getController()->selectAngle(angle);
	return true;
}


AngleChooser::AngleChooser(Board * board): board(board)
{
	for(int i = 0; i < 8; i++){
		btns[i] = new AngleChooserBtn(this,i);
		this->addDescendants(btns[i]);
	}
	this->addTranslation(0,1,0);
	this->disableAll();
}


void AngleChooser::disableAll(){
	for(int i = 0; i < 8; i++){
		btns[i]->setVisible(false);
		btns[i]->setTouchable(false);
	}
}

void AngleChooser::enable(std::vector<int> angles){
	for(std::vector<int>::iterator it = angles.begin(); it != angles.end(); it++){
		btns[*it]->setVisible(true);
		btns[*it]->setTouchable(true);
	}
}

Board * AngleChooser::getBoard(){
	return this->board;
}
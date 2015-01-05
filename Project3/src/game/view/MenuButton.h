#pragma once
#include "../../scenegraph/Node.h"
#include "../controller/TixelController.h"

class TixelController;

class MenuButton:public Node
{
private:
	TixelController * controller;
	int id;
public:
	MenuButton(Node * node,int id);
	void setController(TixelController * controller);
	virtual bool clickHandler();
};


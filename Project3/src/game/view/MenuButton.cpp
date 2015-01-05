#include "MenuButton.h"

MenuButton::MenuButton(Node *node, int id):Node(node), id(id){
}

void MenuButton::setController(TixelController * controller){
	this->setTouchable(true);
	this->controller = controller;
}

bool MenuButton::clickHandler(){
	std::cout << "clicked" << std::endl;
	this->controller->selectButton(this->id);
	return true;
}
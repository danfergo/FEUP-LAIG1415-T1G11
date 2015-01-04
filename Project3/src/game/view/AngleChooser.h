#pragma once
#include "../../scenegraph/Node.h"

#include "Board.h"

class AngleChooser;

class AngleChooserBtn: public Node
{
private:
	int angle;
	AngleChooser * chooser;
public:
	AngleChooserBtn(AngleChooser * chooser, int angle);
	bool clickHandler();
};



class AngleChooser: public Node
{
private:
	AngleChooserBtn * btns[8];
	Board * board;
public:
	AngleChooser(Board * board);
	Board * getBoard();
	void disableAll();
	void enable(std::vector<int> angles);
};


#pragma once

#include "CGFinterface.h"

class Interface: public CGFinterface
{
private:
	int activeCamera;
public:
	Interface(void);
	~Interface(void);
	void initGUI();
	void processGUI(GLUI_Control *ctrl);
};


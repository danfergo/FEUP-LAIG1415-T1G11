#pragma once

#include "CGFinterface.h"

class Interface: public CGFinterface
{
public:
	Interface(void);
	~Interface(void);
	void initGUI();
	void processGUI(GLUI_Control *ctrl);
};


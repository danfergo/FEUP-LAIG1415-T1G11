#pragma once

#include "CGFinterface.h"
#include "Light.h"

class Interface: public CGFinterface
{

private:
	std::vector<Light *> lights;
	int * lightsState;
	int drawingMode;
	int activeCameraPosition;
public:
	Interface(void);
	~Interface(void);
	void initGUI();
	void processGUI(GLUI_Control *ctrl);
};


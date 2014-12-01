#pragma once

#include "CGFinterface.h"
#include "scenegraph/Light.h"

class Interface: public CGFinterface
{

private:
	std::vector<Light *> lights;
	int * lightsState;
	int wind;
	int drawingMode,shaddingMode;
	int activeCameraPosition;
public:
	Interface(void);
	~Interface(void);
	void initGUI();
	void processGUI(GLUI_Control *ctrl);
};


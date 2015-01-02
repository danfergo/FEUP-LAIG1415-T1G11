#pragma once

#include "CGFinterface.h"
#include "Light.h"
#include "Node.h"

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
	virtual void initGUI();
	virtual void processGUI(GLUI_Control *ctrl);
	void performPicking(int x, int y);
	void processHits (std::vector<Node *> & nodes, GLint hits, GLuint buffer[]) ;
	virtual void processMouse(int button, int state, int x, int y) ;
	
};


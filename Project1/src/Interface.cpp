#include "Interface.h"

#include "Light.h"
#include "Scene.h"
#include "scenegraph/Camera.h"
#include <iostream>
#include "CGFapplication.h"

#define LIGHTS_BASE_ID 55
#define CAMERAS_ID	   325
#define DRAWINGMODE_ID	   576
#define SHADDINGMODE_ID	   778
#define SHOWAXIS_ID	   1234


Interface::Interface(void): CGFinterface()
{
}


Interface::~Interface(void)
{
}


void Interface::initGUI()
{
	Scene * scene = ((Scene *)this->scene);
	std::vector<Light *> sceneLights = scene->getLights();
	lightsState = new int[sceneLights.size()];

	GLUI_Panel * panelLights = addPanel("Lights: ", 1);
	int * lightvalue;
	unsigned i = 0;
	for(std::vector<Light *>::iterator it = sceneLights.begin(); it != sceneLights.end() ;it++,i++){
		lights.push_back(*it);
		lightsState[i] = ((*it)->isEnabled() ? 1 : 0);
		addCheckboxToPanel (panelLights,(char *)((*it)->getIdTitle()).c_str(),&lightsState[i], i + LIGHTS_BASE_ID);
	}

	
	addColumn();

	activeCameraPosition = scene->getActiveCameraPosition();

	GLUI_Panel * cameraPanel = addPanel("Cameras: ", 1);
	GLUI_RadioGroup * rgCameras = addRadioGroupToPanel(cameraPanel,&activeCameraPosition, CAMERAS_ID);
	
	std::vector<Camera *> cameras = scene->getCameras();

	unsigned size = i + cameras.size();
	std::vector<Camera *>::iterator it = cameras.begin();	
	for(; it != cameras.end() ;it++){
		addRadioButtonToGroup (rgCameras, (char *)(*it)->getTitle().c_str());
	}

	addColumn();

	drawingMode = scene->getDrawingMode(); 

	GLUI_Panel * drawingModePanel = addPanel("Drawing mode: ", 1);
	GLUI_RadioGroup * rgDrawingMode = addRadioGroupToPanel(drawingModePanel,&drawingMode, DRAWINGMODE_ID);
	addRadioButtonToGroup (rgDrawingMode, "Fill");
	addRadioButtonToGroup (rgDrawingMode, "Line");
	addRadioButtonToGroup (rgDrawingMode, "Point");
	
	addColumn();

	shaddingMode = scene->getShaddingMode(); 

	GLUI_Panel * shaddingModePanel = addPanel("Shadding mode: ", 1);
	GLUI_RadioGroup * rgShaddingMode = addRadioGroupToPanel(shaddingModePanel,&shaddingMode, SHADDINGMODE_ID);
	addRadioButtonToGroup (rgShaddingMode, "Flat");
	addRadioButtonToGroup (rgShaddingMode, "Gouraud");
	
	addColumn();
	
	GLUI_Panel * axisModePanel = addPanel("Axis: ", 1);
	GLUI_RadioGroup * rgAxisMode = addRadioGroupToPanel(axisModePanel,&scene->showAxis, SHOWAXIS_ID);
	addRadioButtonToGroup (rgAxisMode, "Show");
	addRadioButtonToGroup (rgAxisMode, "Hide");
	
}



void Interface::processGUI(GLUI_Control *ctrl)
{ 
	int id = ctrl->get_id();
	Scene * scene = (Scene *)this->scene;
	switch(id){
		case  CAMERAS_ID:
			scene->setActiveCamera(activeCameraPosition);	
			break;
		case DRAWINGMODE_ID:
			scene->setDrawingMode((Scene::DrawingMode)drawingMode);		
			break;
		case SHADDINGMODE_ID:
				scene->setShaddingMode((Scene::ShaddingMode)shaddingMode);		
			break;
		case SHOWAXIS_ID:
			break;
		default:
		if(id >= LIGHTS_BASE_ID  && id <= (LIGHTS_BASE_ID + lights.size())){
			int lpos = id - LIGHTS_BASE_ID; 
			if(lightsState[lpos]) lights[lpos]->enable(); else lights[lpos]->disable(); 
	
		}
	}
}
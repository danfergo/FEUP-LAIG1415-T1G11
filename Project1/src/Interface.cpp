#include "Interface.h"

#include "Light.h"
#include "Scene.h"
#include "scenegraph/Camera.h"
#include <iostream>
#include "CGFapplication.h"

#define LIGHTS_BASE_ID 55
#define CAMERAS_ID	   325
#define DRAWINGMODE_ID	   576
#define GOBACK_ID	   4536

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
	addRadioButtonToGroup (rgDrawingMode, "Wireframe");
	addRadioButtonToGroup (rgDrawingMode, "Line");
	addRadioButtonToGroup (rgDrawingMode, "Point");
	
	addColumn();
	
	this->addButton("Voltar ao menu",GOBACK_ID);
	


	//int x; 

	//addCheckboxToPanel (panel, "Luz sup. esq.", &x, 3);
	//addCheckboxToPanel (panel, "Luz sup. dir.", &x, 4);
	//addCheckboxToPanel (panel, "Luz inf. esq.", &x, 5);
	//addCheckboxToPanel (panel, "Luz inf. dir.", &x, 6);

	/**
	addColumn();

	GLUI_Panel * panel2 = addPanel("Relogio",1);
	addButtonToPanel(panel2, "", 8)->set_name("bla bla ");


	GLUI_Panel * panel4 = addPanel("Janela",1);
	addButtonToPanel(panel4, "", 15)->set_name("Fechar");

	addColumn();


	GLUI_Panel * panel3 = addPanel("Robot",1);

	GLUI_Listbox * listb = addListboxToPanel(panel3, "Textura ",  &x, 9);
	listb->add_item(0,"Predefinicao");
	listb->add_item(1,"Aco");
	listb->add_item(2,"Hip-Hop");
	listb->add_item(3,"Azteca");

	addSeparatorToPanel(panel3);

	addStaticTextToPanel(panel3,"Modo de desenho:");
	GLUI_RadioGroup * rg = addRadioGroupToPanel(panel3,&x, 13);
	addRadioButtonToGroup (rg, "Textured");
	addRadioButtonToGroup (rg, "Wireframe");

	addColumn();

	GLUI_Panel * panel5 = addPanel("Slides",1);

	GLUI_Listbox * lists = addListboxToPanel(panel5, "",  &x, 14);
	lists->add_item(0,"Modelos de Iluminacao");
	lists->add_item(1,"Smooth Shading");
	lists->add_item(2,"Ray Casting"); **/
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
		case GOBACK_ID:
			//glutDestroyWindow(scene->a);
			break;
		default:
		if(id >= LIGHTS_BASE_ID  && id <= (LIGHTS_BASE_ID + lights.size())){
			int lpos = id - LIGHTS_BASE_ID; 
			if(lightsState[lpos]) lights[lpos]->enable(); else lights[lpos]->disable(); 
	
		}
	}
}
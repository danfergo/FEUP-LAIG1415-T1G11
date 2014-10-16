#include "Interface.h"

#include "Light.h"
#include "Scene.h"
#include "scenegraph/Camera.h"
#include <iostream>

Interface::Interface(void): CGFinterface()
{
}


Interface::~Interface(void)
{
}


void Interface::initGUI()
{
	activeCamera = ((Scene *)this->scene)->getActiveCameraPosition();
	std::vector<Light *> lights = ((Scene *)this->scene)->getLights();


	int i = 0;
	GLUI_Panel * panelLights = addPanel("Luzes: ", 1);
	for(std::vector<Light *>::iterator it = lights.begin(); it != lights.end() ;it++){
		(*it)->isEnabled();
		addCheckboxToPanel (panelLights,(char *)((*it)->getIdTitle()).c_str(),(int *)&((*it)->getEnableValue()), i);
	}

	
	addColumn();


	// Jump the first camera..
	GLUI_Panel * cameraPanel = addPanel("Cameras: ", 1);
	GLUI_RadioGroup * rgCameras = addRadioGroupToPanel(cameraPanel,&activeCamera, 123);
	i = 20;
	
	std::vector<Camera *> cameras = ((Scene *)this->scene)->getCameras();

	unsigned size = i + cameras.size();
	std::vector<Camera *>::iterator it = cameras.begin();	
	for(; it != cameras.end() ;it++, i++){
		addRadioButtonToGroup (rgCameras, (char *)(*it)->getTitle().c_str());
		//if(size == i && size != 19){
//			addSeparatorToPanel(cameraPanel);
		//}
	}
		
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
	if(ctrl->get_id() == 123){
		((Scene *)this->scene)->setActiveCamera(activeCamera);	
	}

}
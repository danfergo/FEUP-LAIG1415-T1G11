#include "Interface.h"

#include "Light.h"
#include "Scene.h"
#include "Camera.h"
#include "shaders/FlagShader.h"

#include <iostream>
#include "CGFapplication.h"

#define LIGHTS_BASE_ID 55 // to 63
#define CAMERAS_ID	   325
#define DRAWINGMODE_ID	   576
#define SHADDINGMODE_ID	   778
#define SHOWAXIS_ID	   1234
#define RESETANIMATIONS_ID  327
#define WIND_ID  329


Interface::Interface(void): CGFinterface()
{
}



void Interface::initGUI()
{
	Scene * scene = ((Scene *)this->scene);
	std::vector<Light *> sceneLights = scene->getLights();
	lightsState = new int[sceneLights.size()];

	GLUI_Panel * panelLights = addPanel("Lights: ", 1);
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

	addColumn();
	GLUI_Panel * animationsPanel = addPanel("Animations: ", 1);
	addButtonToPanel(animationsPanel,"Reset",RESETANIMATIONS_ID);
	
	
	wind = FlagShader::wind;
	addColumn();
	GLUI_Panel * flagPanel = addPanel("Flag: ", 1);
	GLUI_Spinner * windSpinner = addSpinnerToPanel (flagPanel,"Wind", 2, &wind, WIND_ID);
	windSpinner->set_int_limits(0,10);

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
		case RESETANIMATIONS_ID:
			scene->resetAnimations();
			break;
		case WIND_ID:
			FlagShader::wind = wind;
			break;
		default:
		if(id >= LIGHTS_BASE_ID  && id <= (LIGHTS_BASE_ID + lights.size())){
			int lpos = id - LIGHTS_BASE_ID; 
			if(lightsState[lpos]) lights[lpos]->enable(); else lights[lpos]->disable(); 
	
		}
	}
}

// buffer to be used to store the hits during picking
#define BUFSIZE 256
GLuint selectBuf[BUFSIZE];

void Interface::performPicking(int x, int y) 
{
	// Sets the buffer to be used for selection and activate selection mode
	glSelectBuffer (BUFSIZE, selectBuf);
	glRenderMode(GL_SELECT);

	// Initialize the picking name stack
	glInitNames();

	// The process of picking manipulates the projection matrix
	// so we will be activating, saving and manipulating it
	glMatrixMode(GL_PROJECTION);

	//store current projmatrix to restore easily in the end with a pop
	glPushMatrix ();

	//get the actual projection matrix values on an array of our own to multiply with pick matrix later
	GLfloat projmat[16];
	glGetFloatv(GL_PROJECTION_MATRIX,projmat);

	// reset projection matrix
	glLoadIdentity();

	// get current viewport and use it as reference for 
	// setting a small picking window of 5x5 pixels around mouse coordinates for picking
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	// this is multiplied in the projection matrix
	gluPickMatrix ((GLdouble) x, (GLdouble) (CGFapplication::height - y), 2.0, 2.0, viewport);

	// multiply the projection matrix stored in our array to ensure same conditions as in normal render
	glMultMatrixf(projmat);


	std::vector<Node *> nodes;
	// force scene drawing under this mode
	// only the names of objects that fall in the 5x5 window will actually be stored in the buffer
	((Scene *)scene)->prepareSelection(nodes);

	// restore original projection matrix
	glMatrixMode (GL_PROJECTION);
	glPopMatrix ();

	glFlush();

	// revert to render mode, get the picking results and process them
	GLint hits;
	hits = glRenderMode(GL_RENDER);
	processHits(nodes, hits, selectBuf); 	

}


void Interface::processHits (std::vector<Node *> & nodes, GLint hits, GLuint buffer[]) 
{
	GLuint *ptr = buffer;
	GLuint mindepth = 0xFFFFFFFF;
	GLuint *selected=NULL;
	GLuint nselected;

	// iterate over the list of hits, and choosing the one closer to the viewer (lower depth)
	for (int i=0;i<hits;i++) {
		int num = *ptr; ptr++;
		GLuint z1 = *ptr; ptr++;
		ptr++;
		if (z1 < mindepth && num>0) {
			mindepth = z1;
			selected = ptr;
			nselected=num;
		}
		for (int j=0; j < num; j++) 
			ptr++;
	}
	
	// if there were hits, the one selected is in "selected", and it consist of nselected "names" (integer ID's)
	if (selected!=NULL)
	{
		// this should be replaced by code handling the picked object's ID's (stored in "selected"), 
		// possibly invoking a method on the scene class and passing "selected" and "nselected"
		printf("Picked ID's: ");
		for (int i=0; i<nselected; i++)
			printf("%d ",selected[i]);
		printf("\n");
		
		for (int i=nselected-1; i>=0; i--){ /** from the inner to the outter **/
			if(!nodes[selected[i]]->clickHandler()){
				break;
			}
		}

	}
	/** else
		printf("Nothing selected while picking \n");	**/
}



void Interface::processMouse(int button, int state, int x, int y) 
{
	CGFinterface::processMouse(button,state, x, y);

	// do picking on mouse press (GLUT_DOWN)
	// this could be more elaborate, e.g. only performing picking when there is a click (DOWN followed by UP) on the same place
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		performPicking(x,y);
}
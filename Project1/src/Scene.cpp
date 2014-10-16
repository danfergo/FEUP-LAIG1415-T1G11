
#include "CGFapplication.h"
#include "Scene.h"
#include "scenegraph\primitives\Toro.h"
#include "CGFappearance.h"	
#include "parser\ANFparser.h"
#include <iostream>

Scene::Scene(): root(NULL), CGFscene(){
	// Default settings ...
	shaddingMode = GOURAUD;
	drawingMode = FILL;
	cullingFace = BACK;
	drawingOrder = CCW;
	for(unsigned i = 0; i < 4; i++) backgroundColor[i]=0.0;
	for(unsigned i = 0; i < 4; i++) ambientLight[i]=0.2;
	lightingEnabled = true;
	doublesidedEnabled = false;
	localIlluminationEnabled = true;
}


void Scene::init() 
{
	// Enables lighting computations
	if(lightingEnabled) glEnable(GL_LIGHTING);

	// Sets up some lighting parameters
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, (doublesidedEnabled ? GL_TRUE : GL_FALSE));
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);  // Define ambient light
	glClearColor(backgroundColor[0],backgroundColor[1],backgroundColor[2],backgroundColor[3]);
	glFrontFace((drawingOrder == CW)? GL_CW : GL_CCW);
	if(cullingFace != NONE){
		glEnable(GL_CULL_FACE);
		glCullFace((cullingFace == FRONT) ? GL_FRONT : ((cullingFace == BACK) ? GL_BACK : GL_FRONT_AND_BACK ));
	} else glDisable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, (drawingMode == POINT) ? GL_POINT : ((drawingMode == LINE) ? GL_LINE : GL_FILL));

	// Defines a default normal
	// glNormal3f(0,0,-1);

	Camera * aCam = (Camera *)activeCamera;
	std::vector<Camera *> systemCameras;
	systemCameras.push_back(new Camera("Debugging camera"));
	cameras.insert(cameras.begin(),systemCameras.begin(),systemCameras.end());
	setActiveCamera(aCam);

	setUpdatePeriod(750);


	float position[3] = {20,20,20} , target[3] = {0,0,0};
	//this->activeCamera = new CameraPerspective("",.1,500,position,target,180.f);

	glEnable(GL_NORMALIZE);
}

void Scene::display() 
{

	// ---- BEGIN Background, camera and axis setup
	
	// Clear image and depth buffer everytime we update the scene
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Initialize Model-View matrix as identity (no transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//set camera
	activeCamera->applyView();

	for(std::vector<Light *>::iterator it = lights.begin(); it != lights.end(); it++)
		if(localIlluminationEnabled && lightingEnabled) (*it)->draw(); else (*it)->disable();
	
	//(new Toro(5,7,10,10))->draw();
	// Draw axis
	axis.draw();
	
    // ---- END Background, camera and axis setup

	// Draw Scene
	if(root != NULL)
		root->processNode(NULL);

	// We have been drawing in a memory area that is not visible - the back buffer, 
	// while the graphics card is showing the contents of another buffer - the front buffer
	// glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
	glutSwapBuffers();
}


void Scene::setRoot(Node * root){
	delete this->root;
	this->root = root;
}

bool Scene::addLight(std::string title,float aa[4],float dd[4],float ss[4],bool enabled,
	float location[4], bool visible,float angle, float exponent,float target[4]){
	Light * light;
	if(lights.size() >= 8)
		return false;	

	unsigned ids[8] = {GL_LIGHT0,GL_LIGHT1,GL_LIGHT2,GL_LIGHT3,GL_LIGHT4,GL_LIGHT5,GL_LIGHT6,GL_LIGHT7};
	light = new Light(ids[lights.size()],location);
	light->setAmbient(aa);
	light->setDiffuse(dd);
	light->setSpecular(ss);
	light->setEnabled(enabled);
	light->setVisible(visible);


	if(target!=NULL){
		light->setTarget(target);
		light->setAngle(angle);
		light->setExponent(exponent);
	}
	light->setIdTitle(title);

	lights.push_back(light);


	return true;
}


void Scene::setShaddingMode(ShaddingMode shaddingMode){
	this->shaddingMode = shaddingMode;
}

void Scene::setDrawingMode(DrawingMode drawingMode){
	this->drawingMode = drawingMode;
}

void Scene::setCullingFace(CullingFace cullingFace){

	this->cullingFace = cullingFace;
}

void Scene::setDrawingOrder(DrawingOrder drawingOrder){
	this->drawingOrder = drawingOrder;
}

void Scene::setBackgroundColor(float backgroundColor[4]){
	for(unsigned i = 0 ; i < 4; i++) this->backgroundColor[i] = backgroundColor[i]; 
}

void Scene::setAmbientLight(float ambientLight[4]){
	for(unsigned i = 0 ; i < 4; i++) this->ambientLight[i] = ambientLight[i];
}

void Scene::setLightingEnabled(bool lightingEnabled){
	this->lightingEnabled = lightingEnabled;
}

void Scene::setDoubleSidedEnabled(bool doublesidedEnabled){
	this->doublesidedEnabled = doublesidedEnabled;
}

void Scene::setLocalIlluminationEnabled(bool localIlluminationEnabled){
	this->localIlluminationEnabled = localIlluminationEnabled;
}

void Scene::update (unsigned long millis){
	/* std::cout << " -------------- refreshing scene -------------- \n " ;
	ANFparser x(ANFparser::PERMISSIVE);
	

	lights.clear();

	x.parse(this,"scene.xml");	
	init(); */
}


std::vector<Light *> Scene::getLights(){
	return lights;
}


void Scene::addCamera(Camera * camera){
	cameras.push_back(camera);
}

void Scene::setActiveCamera(int cameraPosition){
	activeCamera = cameras.at(cameraPosition);	
	activeCameraPosition = cameraPosition;
	CGFapplication::activeApp->forceRefresh();
}

void Scene::setActiveCamera(Camera * camera){
	
	std::vector <Camera *>::iterator it; unsigned i = 0;
	for(it=cameras.begin(); it != cameras.end();it++, i++){
		if(*it == camera){
			setActiveCamera(i);
			break;
		}
	}
}


std::vector<Camera *> Scene::getCameras(){
	return cameras;
}   
 
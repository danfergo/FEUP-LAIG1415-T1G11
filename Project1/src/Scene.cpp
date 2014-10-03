
#include "CGFapplication.h"
#include "Scene.h"

#include <math.h>
#include<iostream>

//float pi = acos(-1.0);
//float deg2rad=pi/180.0;

#include "CGFappearance.h"

//CGFappearance *mat1;

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
	glEnable(GL_LIGHTING);

	// Sets up some lighting parameters
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, CGFlight::background_ambient);  // Define ambient light
	
	// Declares and enables a light

	// Defines a default normal
	glNormal3f(0,0,-1);

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

	// Apply transformations corresponding to the camera position relative to the origin
	CGFscene::activeCamera->applyView();
	
	/*
	float light0_pos[4] = {4.0, 6.0, 7.0, 1.0};
	CGFlight* light0 = new CGFlight(GL_LIGHT5, light0_pos);
	light0->enable();
	light0->draw(); */

	for(std::vector<Light *>::iterator it = lights.begin(); it != lights.end(); it++)
		(*it)->draw();

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
	delete(this->root);
	this->root = root;
}

bool Scene::addLight(float aa[4],float dd[4],float ss[4],bool enabled,
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

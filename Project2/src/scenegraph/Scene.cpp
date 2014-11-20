
#include "CGFapplication.h"
#include "Scene.h"
#include "primitives/Toro.h"
#include "CGFappearance.h"	
#include "../parser/ANFparser.h"
#include <iostream>
#include "primitives/Patch.h"
#include "primitives/Plane.h"
#include "primitives/Flag.h"
#include "../LinearAnimation.h"
#include "../CircularAnimation.h"

int Scene::lightsId[8] = {GL_LIGHT0,GL_LIGHT1,GL_LIGHT2,GL_LIGHT3,GL_LIGHT4,GL_LIGHT5,GL_LIGHT6,GL_LIGHT7};
int Scene::drawingModes[3] = {GL_FILL,GL_LINE,GL_POINT};




long startTime = 0;


Scene::Scene(): root(NULL), CGFscene(), showAxis(1){
	quadric = gluNewQuadric();
	gluQuadricTexture(quadric, GL_TRUE);

	// Default settings ...
	shaddingMode = GOURAUD;
	gluQuadricNormals(quadric,GLU_SMOOTH);
	drawingMode = FILL;
	gluQuadricDrawStyle(quadric,GLU_FILL);
	cullingFace = BACK;
	gluQuadricOrientation(quadric,GLU_OUTSIDE);
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

	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_NORMAL);
	glEnable(GL_MAP2_COLOR_4);
	glEnable(GL_MAP2_COLOR_4);
	glEnable(GL_MAP2_TEXTURE_COORD_2);

	// Sets up some lighting parameters
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, (doublesidedEnabled ? GL_TRUE : GL_FALSE));
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);  // Define ambient light
	glClearColor(backgroundColor[0],backgroundColor[1],backgroundColor[2],backgroundColor[3]);
	glFrontFace((drawingOrder == CW)? GL_CW : GL_CCW);
	if(cullingFace != NONE){
		glEnable(GL_CULL_FACE);
		glCullFace((cullingFace == FRONT) ? GL_FRONT : ((cullingFace == BACK) ? GL_BACK : GL_FRONT_AND_BACK ));
	} else glDisable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, drawingModes[drawingMode]);
	if(shaddingMode == FLAT) glShadeModel(GL_FLAT); else  glShadeModel(GL_SMOOTH);

	Camera * aCam = (Camera *)activeCamera;
	std::vector<Camera *> systemCameras;
	systemCameras.push_back(new Camera("[AUTO] Free camera"));
	cameras.insert(cameras.begin(),systemCameras.begin(),systemCameras.end());
	setActiveCamera(aCam);

	setUpdatePeriod(30);

	Flag::shader = new FlagShader();

	glEnable(GL_NORMALIZE);
	glEnable(GL_AUTO_NORMAL);
}


bool firstDisplay = true;
void Scene::display() 
{

	// ---- BEGIN Background, camera and axis setup
	
	// Clear image and depth buffer everytime we update the scene
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	//redefining some settings that could be changed true the interface
	glPolygonMode(GL_FRONT_AND_BACK, drawingModes[drawingMode]);
	if(shaddingMode == FLAT) glShadeModel(GL_FLAT); else  glShadeModel(GL_SMOOTH);

	// Initialize Model-View matrix as identity (no transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//set camera
	activeCamera->applyView();

	for(std::vector<Light *>::iterator it = lights.begin(); it != lights.end(); it++)
		if(localIlluminationEnabled && lightingEnabled) (*it)->draw(); else (*it)->disable();
	
	// Draw axis
	if(showAxis==0) axis.draw();
	
//	axis.draw();
//	glScaled(5,0.5,5);
	//f->draw(NULL);
	//a->animate();
	//Toro * t = new Toro(0.5, 1, 5, 5);
	//t->draw(NULL);


    // ---- END Background, camera and axis setup
	/*
	FlagShader * flagShader = new FlagShader();
	Flag * f = new Flag(flagShader);
	f->draw(NULL);
	*/
	/*

	
	*/
	
	/*
	Point3d points[9] = {
			{0,0,0},{0,0,1},{0,0,2},
			{1,1,0},{1,1,1},{1,1,2},
			{2,0,0},{2,0,1},{2,0,2}
			};

		Patch * xx = new Patch(2,50, 60, Patch::FILL, points);
		FlagShadder * yy = new FlagShadder();
		yy->bind();
		xx->draw(NULL);
	yy->unbind();

	*/
	// Draw Scene
	if(root != NULL){
		if(firstDisplay){
			root->processNodeInitialization(NULL);
			firstDisplay = false;
		}else{
			root->processNode(NULL);

		}
	}


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
	if(lights.size() >= 8)
		return false;	

	Light * light;
	light = new Light(lightsId[lights.size()],location);
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
	switch(shaddingMode){
		case FLAT: gluQuadricNormals(quadric,GLU_FLAT);
			break;
		case GOURAUD: gluQuadricNormals(quadric,GLU_SMOOTH);
			break;	
	}
}

void Scene::setDrawingMode(DrawingMode drawingMode){
	this->drawingMode = drawingMode;
	switch(drawingMode){
		case FILL: gluQuadricDrawStyle(quadric,GLU_FILL);
			break;
		case LINE: gluQuadricDrawStyle(quadric,GLU_LINE);
			break;	
		case POINT: gluQuadricDrawStyle(quadric,GLU_POINT);
			break;	
	}

}

void Scene::setCullingFace(CullingFace cullingFace){
	this->cullingFace = cullingFace;
	switch(cullingFace){
	case FRONT:
		gluQuadricOrientation(quadric,GLU_INSIDE);
		break;
	default:
		gluQuadricOrientation(quadric,GLU_OUTSIDE);
		break;
	}
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
	if(startTime == 0) startTime = millis;
	root->update(millis-startTime);
	FlagShader::time = millis-startTime;
}


void Scene::resetAnimations(){
	startTime = 0;
}

int Scene::getActiveCameraPosition(){
	std::vector <Camera *>::iterator it; unsigned i = 0;
	for(it=cameras.begin(); it != cameras.end();it++, i++){
		if(*it == activeCamera){
			return i;
		}
	}
	return -1;
}

int Scene::getDrawingMode(){
	return this->drawingMode;
}

int Scene::getShaddingMode(){
	return this->shaddingMode;
}

std::vector<Light *> Scene::getLights(){
	return lights;
}


void Scene::addCamera(Camera * camera){
	cameras.push_back(camera);
}

void Scene::setActiveCamera(int cameraPosition){
	activeCamera = cameras.at(cameraPosition);	
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
 
GLUquadric * Scene::getQuadric(){
	return quadric;
}


#include "Camera.h"
#include "CGFobject.h"


Camera::Camera(std::string title, float near, float far): CGFcamera(), title(title),near(near),far(far){
};


std::string Camera::getTitle() const{
	return this->title;
}

CameraOrtho::CameraOrtho(std::string title, float near, float far, 
	float left, float right,float bottom, float top, CameraOrtho::Axis axis): 
	Camera(title,near,far), left(left),right(right),top(top),bottom(bottom),axis(axis){
}

void CameraOrtho::updateProjectionMatrix(int width, int height){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(left,right,bottom,top,near,far);
}


void CameraOrtho::applyView(){
	if(axis == XX){
		glRotated(-90,0,1,0);
	}else if(axis == YY){
		glRotated(90,1,0,0);
	}
}



CameraPerspective::CameraPerspective(std::string title,float near, float far,
				float pos[3], float target[3],float angle): Camera(title,near,far), aspectRatio(1) , angle(angle){
		this->pos[0] = pos[0];
		this->pos[1] = pos[1];
		this->pos[2] = pos[2];
		this->targ[0] = target[0];
		this->targ[1] = target[1];
		this->targ[2] = target[2];
};

void CameraPerspective::updateProjectionMatrix(int width, int height)
{
	aspectRatio = (float)width / (float)height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	
	gluPerspective(angle,aspectRatio,near,far);
	
}


void CameraPerspective::applyView(){
	gluLookAt(pos[0],pos[1],pos[2],targ[0],targ[1],targ[2],0,1,0);
}
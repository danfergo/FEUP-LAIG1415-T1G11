#include "GameCamera.h"
#include "CGFobject.h"
#include "../../scenegraph/utils/Normals.h"
#include <iostream>

GameCamera::GameCamera(std::string title,float near, float far, float pos[3], float target[3],float angle):
CameraPerspective(title,near,far,pos,target,angle){
	animation = NULL;

}

void GameCamera::produceRotation(float angle, int dur){
	Point2d r = {this->pos[0]-this->targ[0],this->pos[2]-this->targ[2]};
	Point3d  c = {this->targ[0],this->targ[1],this->targ[2]};
	int nn = normals::norm(r);
	normals::normalizeVector(r);
	float initialAngle  = (180*acos(r.y))/(float)acos((double)-1); 
	std::cout <<this->position[0] << " " <<  this->position[2] << std::endl;

	if(animation) delete(animation);
	this->animation = new CircularAnimation(0,5,c,nn,initialAngle,initialAngle+angle);
}

void GameCamera::update(unsigned long ticks){
	if(this->animation != NULL){
		
		this->animation->update(ticks);
		Point3d coords = this->animation->getCurrentPosition();
		
		this->pos[0] = coords.x;
		this->pos[2] = coords.z; 

	}
}


Point3d GameCamera::calcTarget(){
	Point3d  x = {targ[0],targ[1],targ[2]};
	return x;
}


GameCamera::~GameCamera(void)
{
}

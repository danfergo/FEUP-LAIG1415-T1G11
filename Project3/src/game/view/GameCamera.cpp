#include "GameCamera.h"
#include "CGFobject.h"
#include "../../scenegraph/utils/Normals.h"
#include <iostream>

GameCamera::GameCamera(std::string title,float near, float far, float pos[3], float target[3],float angle):
CameraPerspective(title,near,far,pos,target,angle){
	animation = new CircularAnimation(0,0,calcTarget(),0.0,0.0,0.0);

}

void GameCamera::produceRotation(float angle, int dur){
	Point2d x = {this->position[0],this->position[2]};
	
	
	animation = NULL;
	this->animation = new CircularAnimation(0,5,calcTarget(), normals::norm(x),0.0,angle);
}

void GameCamera::update(unsigned long ticks){
	if(this->animation != NULL){
		
		this->animation->update(ticks);
		Point3d coords = animation->getCurrentPosition();
		
		this->pos[0] = coords.x;
		this->pos[2] = coords.z; 

		
	}
}


Point3d GameCamera::calcTarget(){
	Point3d  x = {target[0],target[1],target[2]};
	return x;
}


GameCamera::~GameCamera(void)
{
}

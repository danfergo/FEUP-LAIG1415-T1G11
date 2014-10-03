#include "Light.h"
#include <iostream>


Light::Light(unsigned int lightid, float* pos): CGFlight(lightid,pos), visible(visible){
}

Light::~Light(){

}

void Light::draw(){
	if(visible) 
		CGFlight::draw();
	else
		CGFlight::update();
}

void Light::setEnabled(bool enabled){
	if(enabled){ this->enable(); }else {this->disable();};
}

void Light::setVisible(bool visible){
	this->visible = visible;
}

void Light::setTarget(float target[4]){
	//AB> = B - A 
	float direction[3] = {(target[0]-position[0]),(target[1]-position[1]),(target[2]-position[2])};
	this->direction[0] = direction[0];
	this->direction[1] = direction[1];
	this->direction[2] = direction[2];
}

void Light::setAngle(float angle){
	this->angle = angle;
}
void Light::setExponent(float exponent){
	glLightf(this->id,GL_SPOT_EXPONENT,exponent);
}
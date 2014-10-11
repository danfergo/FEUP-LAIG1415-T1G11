#pragma once

#include "CGFappearance.h"
#include "Texture.h"


class Appearance: public CGFappearance
{
public:
	Appearance(float * a , float * b, float * c , float d):CGFappearance(a,b,c,d){};
	~Appearance(void){};

	Texture * getTexture(){
		return (Texture *)this->texture;	
	}
};


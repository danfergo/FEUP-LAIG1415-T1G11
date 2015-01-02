#include "Appearance.h"



Appearance::Appearance(float * a , float * b, float * c , float d):CGFappearance(a,b,c,d)
{
}


Appearance::~Appearance(void)
{
}


Texture * Appearance::getTexture(){
		return (Texture *)this->texture;	
	}
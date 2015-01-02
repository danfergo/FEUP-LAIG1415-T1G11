#pragma once

#include "CGFappearance.h"
#include "Texture.h"


class Appearance: public CGFappearance
{
public:
	Appearance(float * a , float * b, float * c , float d);
	~Appearance(void);
	Texture * getTexture();
};


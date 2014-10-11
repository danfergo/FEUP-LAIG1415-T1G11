#pragma once

#include "CGFobject.h"
#include "Texture.h"

class Primitive: public CGFobject
{
public:
	Primitive(void){};
	virtual void draw(Texture * texture) const = 0;
	~Primitive(void){};
};


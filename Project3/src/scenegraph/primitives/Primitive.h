#pragma once

#include "CGFobject.h"
#include "../appearances/Texture.h"

class Primitive: public CGFobject
{
private:
	bool visible;
	bool touchable;
public:

	virtual void draw(Texture * texture) = 0;
};


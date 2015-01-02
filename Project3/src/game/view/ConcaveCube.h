#pragma once

#include "../../scenegraph/primitives/Primitive.h"
#include "../../scenegraph/primitives/Retangle.h" 

class ConcaveCube: public Primitive {
private:
	double xis[19];
	double zes[19];
public:
	ConcaveCube(void);
	void draw(Texture * texture);
};
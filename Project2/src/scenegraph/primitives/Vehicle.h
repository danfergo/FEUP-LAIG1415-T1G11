#pragma once

#include "Sphere.h"
#include "Cylinder.h"
#include "../Primitive.h"
#include "../utils/Point.h"
#include "../../CircularAnimation.h"

class Vehicle: public Primitive
{
private:
	GLUquadric * quadric;
	Sphere * corpo;
	Cylinder *cauda, *heliceG, *heliceS, *traseira;
	CircularAnimation * animation;
public:
	Vehicle(void);
	virtual void draw(Texture * texture);
	~Vehicle(void);
};


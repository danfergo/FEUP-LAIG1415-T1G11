#ifndef CYLINDER_F_H
#define CYLINDER_F_H

#include "CGFobject.h"
#include "../utils/Point.h"

class Cylinder: public CGFobject{

private:
	float base, top, height;
	int slices, stacks;
	GLUquadricObj * obj;
	Point2d * vertexBase;

public:
	Cylinder(float base, float top, float height, int slices, int stacks);
	void draw();
	~Cylinder();

};

#endif

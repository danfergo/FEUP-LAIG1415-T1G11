#ifndef CYLINDER_F_H
#define CYLINDER_F_H

#include "../Primitive.h"
#include "../utils/Point.h"

class Cylinder: public Primitive{

private:
	float base, top, height;
	unsigned slices, stacks;
	GLUquadric * obj;
	Point2d *vertexBase, *vertexTop;

public:
	Cylinder(GLUquadric * quadric, float base, float top, float height, unsigned slices, unsigned stacks);
	void draw(Texture * texture);
	~Cylinder();

};

#endif

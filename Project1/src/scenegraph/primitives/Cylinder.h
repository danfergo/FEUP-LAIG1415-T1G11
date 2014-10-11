#ifndef CYLINDER_F_H
#define CYLINDER_F_H

#include "../Primitive.h"
#include "../utils/Point.h"

class Cylinder: public Primitive{

private:
	float base, top, height;
	unsigned slices, stacks;
	GLUquadricObj * obj;
	Point2d * vertexBase;

public:
	Cylinder(float base, float top, float height, unsigned slices, unsigned stacks);
	void draw(Texture * texture) const;
	~Cylinder();

};

#endif

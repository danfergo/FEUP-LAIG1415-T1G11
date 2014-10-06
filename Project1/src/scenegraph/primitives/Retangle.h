#ifndef RETANGLE_F_H
#define RETANGLE_F_H

#include "CGFobject.h"
#include "../utils/Point.h"

class Retangle: public CGFobject
{
private:
	Point2d vertex[2];
	GLUquadricObj * obj;

public:
	Retangle(Point2d vertex[2]);
	void draw();
	~Retangle(void);
};

#endif


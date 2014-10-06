#ifndef TTRIANGLEP_F_H_
#define TTRIANGLEP_F_H_

#include "CGFobject.h"
#include "../utils/Point.h"

class Triangle: public CGFobject
{
private:
	Point3d vertex[3];
	Vector3d normal;

public:
	Triangle(Point3d vertex[3]);
	~Triangle(void);
	void draw();
};

#endif




#ifndef TORO_F_H
#define TORO_F_H

#include "CGFobject.h"
#include "../utils/Point.h"

class Toro: public CGFobject
{
private:
	Point3d ** vertex;
	int slices, loops;
	float raioCentral, raioLateral;

public:
	Toro(float inner, float outer, int slices, int loops);
	void draw();
	~Toro(void);
};

#endif

#ifndef TORO_F_H
#define TORO_F_H

#include "CGFobject.h"
#include "../utils/Point.h"

class Toro: public CGFobject
{
private:
	int slices, loops;
	float inner, outer;

public:
	Toro(float inner, float outer, int slices, int loops);
	void draw();
	~Toro(void);
};

#endif

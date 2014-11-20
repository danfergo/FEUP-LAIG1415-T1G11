#ifndef TORO_F_H
#define TORO_F_H

#include "../Primitive.h"
#include "../utils/Point.h"

class Toro: public Primitive
{
private:
	Point3d ** vertex;
	Vector3d ** normal;
	unsigned slices, loops;
	float raioCentral, raioLateral;

public:
	Toro(float inner, float outer, unsigned slices, unsigned loops);
	void draw(Texture * texture);
	~Toro(void);
};

#endif
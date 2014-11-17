#ifndef PLANE_F_H
#define PLANE_F_H

#include "../Primitive.h"
#include "../utils/Point.h"

class Plane: public Primitive
{
private:
public:
	Plane();
	void draw() const;
	~Plane(void);
};

#endif


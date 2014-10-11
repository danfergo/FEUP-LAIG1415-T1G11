#ifndef RETANGLE_F_H
#define RETANGLE_F_H

#include "../Primitive.h"
#include "../utils/Point.h"

class Retangle: public Primitive
{
private:
	Point2d vertex[2];
	GLUquadricObj * obj;

public:
	Retangle(Point2d vertex[2]);
	void draw(Texture * texture) const;
	~Retangle(void);
};

#endif


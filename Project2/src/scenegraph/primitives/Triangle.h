#ifndef TTRIANGLEP_F_H_
#define TTRIANGLEP_F_H_

#include "../Primitive.h"
#include "../utils/Point.h"

class Triangle: public Primitive
{
private:
	Point3d vertex[3];
	Vector3d normal;
	float height,semibase,base;
public:
	Triangle(Point3d vertex[3]);
	~Triangle(void);
	void draw(Texture * texture) const;
};

#endif




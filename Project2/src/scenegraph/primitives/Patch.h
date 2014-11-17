#ifndef PATCH_F_H
#define PATCH_F_H

#include "../Primitive.h"
#include "../utils/Point.h"

class Patch: public Primitive
{
public:
	typedef enum Compute{
		POINT, LINE, FILL
	}Compute;
private:

	int order, partsU, partsV;
	GLenum compute;
	float * controlPoints;
public:
	Patch(int order, int partsU, int partsV, Compute compute, Point3d * controlpoints);
	void draw(Texture * texture) const;
	~Patch(void);
};

#endif


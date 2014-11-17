#ifndef PATCH_F_H
#define PATCH_F_H

#include "../Primitive.h"
#include "../utils/Point.h"

class Patch: public Primitive
{
private:
	typedef enum Compute{
		POINT, LINE, FILL
	}Compute;
	int order, partsU, partsV;
	Compute compute;
	std::vector<Point3d> controlPoints;
public:
	Patch(int order, int partsU, int partsV, Compute compute, Point3d * controlpoints);
	void draw() const;
	~Patch(void);
};

#endif


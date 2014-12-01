#ifndef PLANE_F_H
#define PLANE_F_H

#include "Patch.h"
#include "../utils/Point.h"

class Plane: public Patch
{
private:
public:
	Plane(unsigned parts);
	Plane(unsigned parts,unsigned sizeX,unsigned sizeZ);
};

#endif


#include "Plane.h"

Plane::Plane(unsigned parts):Patch(1, parts, parts,Patch::FILL)
{	
	Point3d cp[4] = {
		{-0.5,0,-0.5},{-0.5,0,0.5},
		{0.5,0,-0.5},{0.5,0,0.5}
	};

	this->setControlPoints(cp);
}


Plane::Plane(unsigned parts,unsigned sizeX,unsigned sizeZ):Patch(1, parts, parts,Patch::FILL){
	float xx = sizeX/(float)2, zz = sizeZ/(float)2;

	Point3d cp[4] = {
		{-xx,0,-zz},{-xx,0,zz},
		{xx,0,-zz},{xx,0,zz}
	};

	this->setControlPoints(cp);
}
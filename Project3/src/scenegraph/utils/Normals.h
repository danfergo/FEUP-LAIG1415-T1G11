#ifndef NORMALS_H_F_
#define NORMALS_H_F_

#include "Point.h"

namespace normals{
	
	void calculateSurfaceNormalTriangle(const Point3d triangle[3], Vector3d & normal);
	void calculateSurfaceNormal(const Point3d * polygon,unsigned nVertex , Vector3d & normal);
	void normalizeVector(Vector3d & vector);
	double norm(const Vector3d & vector);
	void normalizeVector(Vector2d & vector);
	double norm(const Vector2d & vector);

}

#endif
#ifndef MYSEMISPHERE_X
#define MYSEMISPHERE_X

#include "CGFobject.h"
#include "CGFappearance.h"
#include "CGFlight.h"
#include "../utils/Point.h"


class Sphere: public CGFobject{
	private:
		float angle_a, angle_b;
		unsigned stacks, slices;
		Point3d ** dots;
		
	public:
		Sphere(unsigned stacks, unsigned slices);
		void draw();
		~Sphere();
};

#endif
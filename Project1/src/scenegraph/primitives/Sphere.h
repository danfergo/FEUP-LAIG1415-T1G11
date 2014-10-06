#ifndef MYSEMISPHERE_X
#define MYSEMISPHERE_X

#include "CGFobject.h"
#include "CGFappearance.h"
#include "CGFlight.h"
#include "../utils/Point.h"


class Sphere: public CGFobject{
	private:
		float radius;
		int stacks, slices;
		GLUquadricObj * obj;
		
	public:
		Sphere(float radius, int stacks, int slices);
		void draw();
		~Sphere();
};

#endif
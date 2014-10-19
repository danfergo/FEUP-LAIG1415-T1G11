#ifndef MYSEMISPHERE_X
#define MYSEMISPHERE_X

#include "../Primitive.h"
#include "CGFappearance.h"
#include "CGFlight.h"
#include "../utils/Point.h"


class Sphere: public Primitive{
	private:
		float radius;
		int stacks, slices;
		GLUquadricObj * obj;
		
	public:
		Sphere(GLUquadric *quadric, float radius, int stacks, int slices);
		void draw(Texture * texture) const;
		~Sphere();
};

#endif
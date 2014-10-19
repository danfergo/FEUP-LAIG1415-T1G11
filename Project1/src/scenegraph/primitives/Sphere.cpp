#include "Sphere.h"
#include <math.h>

Sphere::Sphere(GLUquadric *quadric, float radius, int stacks, int slices){
	this->radius = radius;
	this->stacks = stacks;
	this->slices = slices;
    obj = quadric;
}

void Sphere::draw(Texture * texture) const{
	gluSphere(obj, radius, stacks, slices);
} 

Sphere::~Sphere() {
}

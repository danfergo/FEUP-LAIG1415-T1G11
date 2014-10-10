#include "Sphere.h"
#include <math.h>

Sphere::Sphere(float radius, int stacks, int slices){
	this->radius = radius;
	this->stacks = stacks;
	this->slices = slices;
    obj = gluNewQuadric();
	gluQuadricTexture(obj,1);
}

void Sphere::draw(){
	gluSphere(obj, radius, stacks, slices);
} 

Sphere::~Sphere(){
}

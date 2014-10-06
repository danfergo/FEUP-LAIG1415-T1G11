#include "Toro.h"
#include "../utils/Normals.h"
#include <math.h>
#include <iostream>
static float const PI = acos(-1.0);

Toro::Toro(float inner, float outer, int slices, int loops){
	this->inner = inner; 
	this->outer = outer;
	this->slices = slices;
	this->loops = loops;
}

void Toro::draw(){
	glutSolidTorus(inner, outer, slices, loops);
}

Toro::~Toro(void)
{
}

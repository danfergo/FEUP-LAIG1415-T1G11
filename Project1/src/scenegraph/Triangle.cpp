#include "Triangle.h"

#include <iostream>

Triangle::Triangle(Point3d vertex[3]){
	for(unsigned i = 0; i < 3; i++)
		this->vertex[i] = vertex[i];
}

Triangle::~Triangle(void)
{
	
}


void Triangle::draw(){
	glBegin(GL_TRIANGLES);
		for(unsigned i = 0; i < 3; i++)
			glVertex3f(vertex[i].x,vertex[i].y,vertex[i].z);
	glEnd();
}
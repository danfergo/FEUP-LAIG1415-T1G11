#include "Triangle.h"

#include <iostream>
#include "../utils/Normals.h"

Triangle::Triangle(Point3d vertex[3]){
	for(unsigned i = 0; i < 3; i++)
		this->vertex[i] = vertex[i];
	
	normals::calculateSurfaceNormal(this->vertex,3,this->normal);
}

Triangle::~Triangle(void)
{
	
}

void Triangle::draw(){
	
	glNormal3f(normal.x,normal.y,normal.z);
	glBegin(GL_TRIANGLES);
			glTexCoord2f(1,0);
			glVertex3f(vertex[0].x,vertex[0].y,vertex[0].z);
			glTexCoord2f(0.5,1);
			glVertex3f(vertex[1].x,vertex[1].y,vertex[1].z);
			glTexCoord2f(0,0);
			glVertex3f(vertex[2].x,vertex[2].y,vertex[2].z);
	glEnd();
}
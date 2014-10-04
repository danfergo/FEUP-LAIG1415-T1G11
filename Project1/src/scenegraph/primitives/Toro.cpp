#include "Toro.h"
#include <math.h>

static float const PI = acos(-1.0);

Toro::Toro(float inner, float outer, int slices, int loops): slices(slices), loops(loops) 
{
	vertex = new Point3d* [slices];
	for (unsigned i = 0; i < slices; ++i)
		vertex[i] = new Point3d[loops];

	this->raioCentral = (outer-inner)/2;
	this->raioLateral = raioCentral-inner;

	float alpha = 2*PI/slices;
	float beta = 2*PI/loops;

	for(unsigned i=0; i<slices; i++){
		alpha*=i;
		float fator = raioCentral+raioLateral*cos(alpha);

		for(unsigned j=0; j<loops; j++){
			beta*=j;
			vertex[i][j].x = fator*cos(beta);
			vertex[i][j].y = fator*sin(beta);
			vertex[i][j].z = raioLateral*sin(alpha);
		}
	}
}

void Toro::draw(){
	glPushMatrix();

	for(unsigned i=0; i<slices; i++){
		glBegin(GL_TRIANGLE_STRIP);
		for(unsigned j=0; j<loops; j++){
			glNormal3d(0,1,0);
			glVertex3f(vertex[i][j].x,vertex[i][j].y,vertex[i][j].z);
			glNormal3d(0,1,0);
			glVertex3f(vertex[i][j].x,vertex[i][j].y,vertex[i][j].z);
		}
		glEnd();
	}
	glPopMatrix();
}

Toro::~Toro(void)
{
	for(unsigned i=0; i<slices; i++)
		delete[] vertex[i];
	delete[] vertex;
}

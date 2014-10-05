#include "Toro.h"
#include "../utils/Normals.h"
#include <math.h>
#include <iostream>
static float const PI = acos(-1.0);

Toro::Toro(float inner, float outer, int slices, int loops): slices(slices), loops(loops) 
{
	vertex = new Point3d* [slices+1];
	normal = new Vector3d* [slices+1];
	for (unsigned i = 0; i <= slices; ++i){
		vertex[i] = new Point3d[loops+1];
		normal[i] = new Vector3d[loops+1];
	}

	this->raioCentral = (outer-inner)/2 + inner;
	this->raioLateral = raioCentral-inner;

	float alphaMin = 2*PI/slices;
	float betaMin = 2*PI/loops;

	for(unsigned i=0; i<=slices; i++){
		float alpha = alphaMin*i;
		float fator = raioCentral+raioLateral*cos(alpha);

		for(unsigned j=0; j<=loops; j++){
			float beta = betaMin*j;
			vertex[i][j].x = fator*cos(beta);
			vertex[i][j].y = fator*sin(beta);
			vertex[i][j].z = raioLateral*sin(alpha);
		}
	}

	Point3d triangle[3];
	char arrayfull = 0;
	int pos=0;
	for(unsigned i=0; i<=slices; i++){
		for(unsigned j=0; j<=loops; j++, pos=abs((pos-1)%3)){
			triangle[2-pos]=vertex[i][j];
			if(arrayfull>2){
				normals::calculateSurfaceNormalTriangle(triangle,normal[i][j]);
			}
			else {
				normal[i][j].x=0;
				normal[i][j].y=0;
				normal[i][j].z=0;
				arrayfull++;
			}
		}
	}

}

void Toro::draw(){

	glPushMatrix();

	for(unsigned i=0; i<slices; i++){
		glPushMatrix();
		glBegin(GL_TRIANGLE_STRIP);
		for(unsigned j=0; j<=loops; j++){
			glNormal3d(normal[i][j].x,normal[i][j].y,normal[i][j].z);
			glVertex3f(vertex[i][j].x,vertex[i][j].y,vertex[i][j].z);

			glNormal3d(normal[i+1][j].x,normal[i+1][j].y,normal[i+1][j].z);
			glVertex3f(vertex[i+1][j].x,vertex[i+1][j].y,vertex[i+1][j].z);
		}
		glEnd();
		glPopMatrix();
	}

	glPopMatrix();
}

Toro::~Toro(void)
{
	for(unsigned i=0; i<=slices; i++)
		delete[] vertex[i];
	delete[] vertex;
}

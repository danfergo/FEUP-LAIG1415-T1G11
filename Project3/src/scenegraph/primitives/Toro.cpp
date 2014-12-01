#include "Toro.h"
#include "../utils/Normals.h"
#include <math.h>
#include <iostream>
static float const PI = acos(-1.0);

Toro::Toro(float inner, float outer, unsigned slices, unsigned loops): slices(slices), loops(loops) 
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

			normal[i][j].x = fator*cos(beta) - raioCentral*cos(beta);
			normal[i][j].y = fator*sin(beta) - raioCentral*sin(beta);
			normal[i][j].z = raioLateral*sin(alpha);
		}
	}

}

void Toro::draw(Texture * texture){
	glPushMatrix();
		for(unsigned j=0; j<loops; j++){
		
			glPushMatrix();
			glBegin(GL_TRIANGLE_STRIP);
				for(unsigned i=0; i<=slices; i++){
					glTexCoord2d((i)*(1/(float)slices),0);
					glNormal3d(normal[i][j].x,normal[i][j].y,normal[i][j].z);
					glVertex3f(vertex[i][j].x,vertex[i][j].y,vertex[i][j].z);

					glTexCoord2d((i +1)*(1/(float)slices),1);
					glNormal3d(normal[i][j+1].x,normal[i][j+1].y,normal[i][j+1].z);
					glVertex3f(vertex[i][j+1].x,vertex[i][j+1].y,vertex[i][j+1].z);
			
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
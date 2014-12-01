#include "Cylinder.h"
#include <math.h>

static float const PI = acos(-1.0);

Cylinder::Cylinder(GLUquadric*quadric, float base, float top, float height, unsigned slices, unsigned stacks)
{
	this->base = base;
	this->top = top;
	this->height = height;
	this->slices = slices;
	this->stacks = stacks;
    obj = quadric;
	vertexBase = new Point2d[slices];
	vertexTop = new Point2d[slices];

	float alphaMin = 2*PI/slices;

	for(unsigned i=0; i<slices; i++){
		float alpha=alphaMin*i;

		vertexBase[i].x = sin(alpha)*base;
		vertexBase[i].y = cos(alpha)*base; 

		vertexTop[i].x = sin(alpha)*top;
		vertexTop[i].y = cos(alpha)*top;
	
		
	}
}

void Cylinder::draw(Texture * texture){
    gluCylinder(obj, base, top, height, slices, stacks);
	
	glNormal3d(0,0,-1);
	glBegin(GL_POLYGON);
		for(unsigned i = 0; i < slices; i++){
			glTexCoord2d(vertexBase[i].x,vertexBase[i].y);
			glVertex3d(vertexBase[i].x,vertexBase[i].y,0);
		}
	glEnd();

	glNormal3d(0,0,1);
	glBegin(GL_POLYGON);
				for(unsigned i = slices; i > 0; i--){
					glTexCoord2d(vertexTop[i-1].x,vertexTop[i-1].y);
			glVertex3d(vertexTop[i-1].x,vertexTop[i-1].y,height);
		}
	glEnd();
}

Cylinder::~Cylinder(void)
{
}

#include "Cylinder.h"
#include <math.h>

static float const PI = acos(-1.0);

Cylinder::Cylinder(float base, float top, float height, unsigned slices, unsigned stacks)
{
	this->base = base;
	this->top = top;
	this->height = height;
	this->slices = slices;
	this->stacks = stacks;
    obj = gluNewQuadric();
	gluQuadricTexture(obj,1);
	vertexBase = new Point2d[slices];
	vertexTop = new Point2d[slices];

	float alphaMin = 2*PI/slices;

	for(unsigned i=0; i<slices; i++){
		float alpha=alphaMin*i + PI/slices;

		vertexBase[i].x = cos(alpha)*base; 
		vertexBase[i].y = sin(alpha)*base;

		vertexBase[i].x = cos(alpha)*top; 
		vertexBase[i].y = sin(alpha)*top;
	
		
	}
}

void Cylinder::draw(Texture * texture) const{
    gluCylinder(obj, base, top, height, slices, stacks);
	
	glNormal3d(0,0,-1);
	glBegin(GL_POLYGON);
		for(unsigned i = slices; i > 0; i--){
			glVertex3d(vertexBase[i-1].x,vertexBase[i-1].y,0);
		}
	glEnd();

	glNormal3d(0,0,1);
	glBegin(GL_POLYGON);
		for(unsigned i = 0; i < slices; i++){
			glVertex3d(vertexTop[i].x,vertexTop[i].y,height);
		}
	glEnd();
}

Cylinder::~Cylinder(void)
{
}

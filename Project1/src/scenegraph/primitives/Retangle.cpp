#include "Retangle.h"
#include <stdlib.h> 

Retangle::Retangle(Point2d vertex[2])
{
	this->vertex[0] = vertex [0];
	this->vertex[1] = vertex [1];
}

void Retangle::draw(Texture * texture) const{
	float textS = (texture==NULL || texture->getS()==0) ? 0 : abs(vertex[1].x-vertex[0].x)/texture->getS();
	float textT = (texture==NULL || texture->getT()==0)? 0 : abs(vertex[1].y-vertex[0].y)/texture->getT();

	glNormal3f(0,0,1);
	glBegin(GL_POLYGON);
		glTexCoord2f(0,0);
		glVertex3d(vertex[0].x,vertex[0].y,0);

		glTexCoord2f(textS,0);
		glVertex3d(vertex[1].x,vertex[0].y,0);
		
		glTexCoord2f(textS,textT);
		glVertex3d(vertex[1].x,vertex[1].y,0);
		
		glTexCoord2f(0,textT);
		glVertex3d(vertex[0].x,vertex[1].y,0);
	glEnd();

}

Retangle::~Retangle(void)
{
}
	
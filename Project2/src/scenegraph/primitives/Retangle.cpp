#include "Retangle.h"
#include <stdlib.h> 

Retangle::Retangle(Point2d v[2])
{
	this->vertex[0] = v[0];
	this->vertex[2] = v[1];

	m = (this->vertex[2].y - this->vertex[0].y)/(this->vertex[2].x - this->vertex[0].x);
	if(m >= 0){
		vertex[1].x = vertex[2].x;
		vertex[1].y = vertex[0].y;
		vertex[3].x = vertex[0].x;
		vertex[3].y = vertex[2].y;
	}else{
		vertex[1].x = vertex[0].x;
		vertex[1].y = vertex[2].y;
		vertex[3].x = vertex[2].x;
		vertex[3].y = vertex[0].y;
	}


}

void Retangle::draw(Texture * texture){
	float textS = 0,textT  = 0;
	if(m>=0 && !(texture==NULL || texture->getS()==0)){
		textS = abs(vertex[1].x-vertex[0].x)/texture->getS();
		textT = abs(vertex[3].y-vertex[0].y)/texture->getT();
	}else if(!(texture==NULL || texture->getS()==0)){
		textS = abs(vertex[1].y-vertex[0].y)/texture->getS();
		textT = abs(vertex[3].x-vertex[0].x)/texture->getT();
	}


	glNormal3f(0,0,1);
	glBegin(GL_POLYGON);
		glTexCoord2f(0,0);
		glVertex3d(vertex[0].x,vertex[0].y,0);

		glTexCoord2f(textS,0);
		glVertex3d(vertex[1].x,vertex[1].y,0);
		
		glTexCoord2f(textS,textT);
		glVertex3d(vertex[2].x,vertex[2].y,0);
		
		glTexCoord2f(0,textT);
		glVertex3d(vertex[3].x,vertex[3].y,0);
	glEnd();

}

Retangle::~Retangle(void)
{
}
	
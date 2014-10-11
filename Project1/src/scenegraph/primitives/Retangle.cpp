#include "Retangle.h"


Retangle::Retangle(Point2d vertex[2])
{
	this->vertex[0] = vertex [0];
	this->vertex[1] = vertex [1];
}

void Retangle::draw(Texture * texture) const{
	glNormal3f(0,0,1);
	glRectf(vertex[0].x, vertex[0].y, vertex[1].x, vertex[1].y);
}

Retangle::~Retangle(void)
{
}
	
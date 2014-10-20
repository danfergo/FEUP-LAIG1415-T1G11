#include "Triangle.h"

#include "../utils/Normals.h"

Triangle::Triangle(Point3d vertex[3]){
	for(unsigned i = 0; i < 3; i++)
		this->vertex[i] = vertex[i];
	
	normals::calculateSurfaceNormal(this->vertex,3,this->normal);

	float hipo;

	Vector3d v13 = {vertex[2].x - vertex[0].x,vertex[2].y - vertex[0].y ,vertex[2].z - vertex[0].z };
	hipo =  normals::norm(v13);
	Vector3d v12 = {vertex[1].x - vertex[0].x,vertex[1].y - vertex[0].y ,vertex[1].z - vertex[0].z };
	this->base = normals::norm(v12);
	normals::normalizeVector(v13);
	normals::normalizeVector(v12);
	//a × b = [a2b3 − a3b2, a3b1 − a1b3, a1b2 − a2b1].
	Vector3d v13xv12 = { v13.y*v12.z - v13.z*v12.y,v13.z*v12.x - v13.x*v12.z, v13.x*v12.y - v13.y*v12.x };
	Vector3d v13v12 = {v13.x*v12.x , v13.y*v12.y, v13.z*v12.z};
	this->height = hipo * normals::norm(v13xv12);
	this->semibase = hipo * normals::norm(v13v12);
}

Triangle::~Triangle(void)
{
	
}

void Triangle::draw(Texture * texture) const{
	float textS = (texture==NULL || texture->getS()==0) ? 0 : this->base/texture->getS();
	float textT3 = (texture==NULL || texture->getT()==0)? 0 : this->height/texture->getT();
	float textS3 = (texture==NULL || texture->getS()==0) ? 0 : this->semibase/texture->getS();

	glNormal3f(normal.x,normal.y,normal.z);
	glBegin(GL_TRIANGLES);
			glTexCoord2f(0,0);
			glVertex3f(vertex[0].x,vertex[0].y,vertex[0].z);
			glTexCoord2f(textS,0);
			glVertex3f(vertex[1].x,vertex[1].y,vertex[1].z);
			glTexCoord2f(textS3,textT3);
			glVertex3f(vertex[2].x,vertex[2].y,vertex[2].z);
	glEnd();
}
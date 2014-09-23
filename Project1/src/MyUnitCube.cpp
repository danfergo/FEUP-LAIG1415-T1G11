#include "MyUnitCube.h"


void MyUnitCube::draw(){
		glPushMatrix();  // front 
		glTranslatef(0,0,0.5);
		glRectf(-0.5,-0.5,0.5,0.5);
	glPopMatrix();
	 
	glPushMatrix(); // top 
		glTranslatef(0,0.5,0);
		glRotated(-90,1,0,0);
		glRectf(-0.5,-0.5,0.5,0.5);
	glPopMatrix();

	glPushMatrix(); // back 
		glTranslatef(0,0,-0.5);
		glRectf(-0.5,0.5,0.5,-0.5);  // drawing counterclockwise:  top left, bottom right
	glPopMatrix();

	glPushMatrix(); // bottom 
		glTranslatef(0,-0.5,0);
		glRotated(90,1,0,0);
		glRectf(-0.5,-0.5,0.5,0.5);
	glPopMatrix();

	glPushMatrix(); // left 
		glTranslatef(-0.5,0,0);
		glRotated(-90,0,1,0);
		glRectf(-0.5,-0.5,0.5,0.5);
	glPopMatrix();

	glPushMatrix(); // right 
		glTranslatef(0.5,0,0);
		glRotated(90,0,1,0);
		glRectf(-0.5,-0.5,0.5,0.5);
	glPopMatrix();
};
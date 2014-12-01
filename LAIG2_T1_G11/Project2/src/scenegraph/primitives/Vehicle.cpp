#include "Vehicle.h"


Vehicle::Vehicle(void)
{
	this->quadric =  gluNewQuadric();
	corpo = new Sphere(this->quadric, 3, 10, 10);
	cauda = new Cylinder( this->quadric,  0.4, 0.2, 12.1, 8, 8);
	heliceG = new Cylinder( this->quadric,  0.1, 0.25, 8, 4, 4);
	heliceS = new Cylinder( this->quadric,  0.07, 0.15, 2, 4, 4);
	traseira = new Cylinder( this->quadric,  0.07, 0.15, 0.5, 4, 4);
	Point3d center = {0,0,0};
	//animation = CircularAnimation(long st,long dur, center, 0, 60,360);
}


Vehicle::~Vehicle(void)
{/*
	delete corpo;
	delete cauda;
	delete heliceG;
	delete heliceS;
	delete traseira;
	delete quadric;*/
}


void Vehicle::draw(Texture * texture){
	
	glPushMatrix();
		glRotatef(90, 0,1,0);
		glScalef(1.5,1,1);
		corpo->draw(texture);
	glPopMatrix();

	glPushMatrix();
		cauda->draw(texture);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(0,3.2,0);

		glPushMatrix();
		glRotatef(90, 0,1,0);
		heliceG->draw(texture);
		glPopMatrix();
		
		glPushMatrix();
		glRotatef(180, 0,1,0);
		heliceG->draw(texture);
		glPopMatrix();
		
		glPushMatrix();
		glRotatef(270, 0,1,0);
		heliceG->draw(texture);
		glPopMatrix();
		
		glPushMatrix();
		heliceG->draw(texture);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.55,0,12);
		glRotatef(90,0,0,1);

		glPushMatrix();
		glRotatef(90, 1,0,0);
		traseira->draw(texture);
		glPopMatrix();

		glPushMatrix();
		glRotatef(90, 0,1,0);
		heliceS->draw(texture);
		glPopMatrix();

		glPushMatrix();
		glRotatef(180, 0,1,0);
		heliceS->draw(texture);
		glPopMatrix();
		
		glPushMatrix();
		glRotatef(270, 0,1,0);
		heliceS->draw(texture);
		glPopMatrix();
		
		glPushMatrix();
		heliceS->draw(texture);
		glPopMatrix();
	glPopMatrix();
}
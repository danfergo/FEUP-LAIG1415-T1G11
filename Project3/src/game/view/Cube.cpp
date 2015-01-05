#include "Cube.h"
#include <stdlib.h>


using namespace std;

Cube::Cube()
{
	float amb[4] = {0.5, 0.5, 0.5, 0};
	float dif[4] = {0.5, 0.5, 0.5, 0};
	float spec[4] = {0.5, 0.5, 0.5, 0};
	
	aparencia = new Appearance(amb,dif,spec, 5.0);

	score = 0;
	
	textura[0] = new Texture("resources/labels/s0.png",1.00,1.00);
/**	textura[1] = new Texture("resources/labels/um.jpg",1.00,1.00);
	textura[2] = new Texture("resources/labels/dois.jpg",1.00,1.00);
	textura[3] = new Texture("resources/labels/tres.jpg",1.00,1.00);
	textura[4] = new Texture("resources/labels/quatro.jpg",1.00,1.00);
	textura[5] = new Texture("resources/labels/cinco.jpg",1.00,1.00); **/


	aparencia->setTexture(textura[score]);
	
	Point2d vertex[2] = {{-0.5,-0.5},{0.5,0.5}};
	retangulo = new Retangle(vertex);
}



void Cube::draw(Texture * texture){
	aparencia->apply();
	
	glPushMatrix();
		glTranslatef(0,0,0.5);
		retangulo->draw(aparencia->getTexture());
	glPopMatrix();
	glPushMatrix();
		glRotatef(90,0,1,0);
		glTranslatef(0,0,0.5);
		retangulo->draw(aparencia->getTexture());
	glPopMatrix();
	glPushMatrix();
		glRotatef(180,0,1,0);
		glTranslatef(0,0,0.5);
		retangulo->draw(aparencia->getTexture());
	glPopMatrix();
	glPushMatrix();
		glRotatef(270,0,1,0);
		glTranslatef(0,0,0.5);
		retangulo->draw(texture);
	glPopMatrix();
	glPushMatrix();
		glRotatef(90,1,0,0);
		glTranslatef(0,0,0.5);
		retangulo->draw(aparencia->getTexture());
	glPopMatrix();
	glPushMatrix();
		glRotatef(270,1,0,0);
		glTranslatef(0,0,0.5);
		retangulo->draw(aparencia->getTexture());
	glPopMatrix();
}

Cube::~Cube(void)
{
}

BackCube::BackCube():Cube(){
	aparencia->setTexture(new Texture("resources/labels/sBack.png",1.00,1.00));
}
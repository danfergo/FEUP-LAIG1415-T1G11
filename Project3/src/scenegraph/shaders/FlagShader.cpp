#include "FlagShader.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

static float PI =acos(-1.0);
int FlagShader::wind = 5;
int FlagShader::time = 0;


CGFtexture * FlagShader::activeTexture = NULL;


FlagShader::FlagShader()
{
	init("resources/shaders/flagshader.vert", "resources/shaders/flagshader.frag");

	timeLoc = glGetUniformLocation(id(),"time");
	piLoc = glGetUniformLocation(id(),"pi");
	windLoc = glGetUniformLocation(id(),"wind");
	baseImageLoc = glGetUniformLocation(id(),"baseImage");
}


unsigned FlagShader::getWind() const{
	return wind;
}

void FlagShader::bind(){
	CGFshader::bind();
	glUniform1i(timeLoc, (int)time);
	glUniform1i(windLoc, (int)wind);
	glUniform1f(piLoc, PI);
	glUniform1i(baseImageLoc,0);
	glActiveTexture(GL_TEXTURE0);
	if(activeTexture)activeTexture->apply();
}
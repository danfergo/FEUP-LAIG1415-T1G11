#include "Flag.h"
#include <iostream>

FlagShader * Flag::shader = NULL;


Flag::Flag(std::string tex): Plane(100,1,1)
{
	texture = new CGFtexture(tex);
}

void Flag::draw(Texture * texture){
	FlagShader::activeTexture = this->texture;
	shader->bind();
		Plane::draw(texture);
	shader->unbind();
}
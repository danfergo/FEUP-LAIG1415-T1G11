#include "Texture.h"
#include <iostream>

Texture::Texture(std::string file, float s, float t):CGFtexture(file){
	this->textlength_s = s;
	this->textlength_t = t;
};


float Texture::getS(){
	return this->textlength_s;
}
float Texture::getT(){
	return this->textlength_t;
}
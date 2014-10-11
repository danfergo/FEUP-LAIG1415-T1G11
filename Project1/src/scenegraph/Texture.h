#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "CGFtexture.h"

class Texture: public CGFtexture
{
private:
	float textlength_s, textlength_t;
public:
	Texture(std::string file, float s, float t);
	float getS();
	float getT();
	~Texture(void){};
};

#endif
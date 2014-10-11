#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "CGFtexture.h"

class Texture: public CGFtexture
{
private:
	float s, t;
public:
	Texture(std::string file, float s, float t):CGFtexture(file), s(s),t(t){};
	float getS() const{
		return s;
	};
	float getT() const{
		return t;
	};
	~Texture(void){};
};

#endif
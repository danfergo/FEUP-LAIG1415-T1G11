#pragma once
#include "../../FlagShader.h"
#include "Plane.h"

class Flag: public Plane
{
private:
	CGFtexture * texture;
public:
	static FlagShader * shader;
	Flag(std::string texture);
	void draw(Texture * notused);
};


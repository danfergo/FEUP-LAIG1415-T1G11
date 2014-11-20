#pragma once
#include "CGFshader.h"
#include "CGFtexture.h"

class FlagShader: public CGFshader
{
private:
	int timeLoc, piLoc, windLoc,baseImageLoc;
public:
	static int wind;
	static int time;
	static CGFtexture * activeTexture;
	FlagShader();
	void bind();
	unsigned getWind() const;
};


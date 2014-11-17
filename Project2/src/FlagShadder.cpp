#include "FlagShadder.h"


FlagShadder::FlagShadder(void)
{
	init("flagshader.vert", "flagshader.frag");

	CGFshader::bind();
}


FlagShadder::~FlagShadder(void)
{
	CGFshader::bind();
}

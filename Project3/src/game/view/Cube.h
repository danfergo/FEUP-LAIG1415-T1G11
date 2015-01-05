#ifndef CUBE_F_H
#define CUBE_F_H
#include "../../scenegraph/appearances/Appearance.h"
#include "../../scenegraph/primitives/Primitive.h"
#include "../../scenegraph/utils/Point.h"
#include "../../scenegraph/primitives/Retangle.h"

class Cube: public Primitive
{
protected:
	int score;
	Texture * textura[6];
	Appearance * aparencia;
	Retangle * retangulo;
public:
	Cube();
	void draw(Texture * texture);
	~Cube(void);
};

class BackCube: public Cube {
public:
	BackCube();
};


#endif
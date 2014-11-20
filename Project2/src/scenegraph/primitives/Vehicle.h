#pragma once
#include "../Primitive.h"

class Vehicle: public Primitive
{
public:
	Vehicle(void);
	virtual void draw(Texture * texture);
	~Vehicle(void);
};


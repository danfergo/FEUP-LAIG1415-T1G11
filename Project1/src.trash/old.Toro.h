#ifndef TORO_F_H
#define TORO_F_H

#include "../Primitive.h"
#include "../utils/Point.h"

class Toro: public Primitive
{
private:
	int slices, loops;
	float inner, outer;

public:
	Toro(float inner, float outer, int slices, int loops);
	void draw(Texture * texture) const;
	~Toro(void);
};

#endif

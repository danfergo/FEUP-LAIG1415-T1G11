#pragma once
#include "GameState.h"

typedef struct IJ {
	int i;
	int j;
} IJ;

typedef struct IJA {
	int i;
	int j;
	int angle;
} IJA;

class Move
{
private:
	GameState *start, *end;
	IJA from, to;
public:
	Move(void);
	~Move(void);
};


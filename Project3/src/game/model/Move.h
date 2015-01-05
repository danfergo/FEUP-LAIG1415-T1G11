#pragma once
#include "GameState.h"


class IJ {
	public:
		IJ(int i, int j);
		IJ();
		bool undefined;
		int i;
		int j;
		void set(int i, int j);
		bool isOutOfBoard();
		std::string toString();
};

class Move
{
	public:
		IJ from, to;
		int fromA, toA;
		
		Move(void);
};


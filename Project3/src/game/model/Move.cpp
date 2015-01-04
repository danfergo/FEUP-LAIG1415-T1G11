#include "Move.h"

#include <sstream>

Move::Move(void):fromA(-1),toA(-1)
{
}


IJ::IJ(int i, int j): i(i),j(j),undefined(true){
}

IJ::IJ():undefined(false){
}
void IJ::set(int i, int j){
	this->i = i;
	this->j = j;
}

bool IJ::isOutOfBoard(){
	return j < 0 || j > 5;
}

std::string IJ::toString(){
	std::stringstream r;
	r << "[" << i << "," << j << "]";
	return r.str();
}
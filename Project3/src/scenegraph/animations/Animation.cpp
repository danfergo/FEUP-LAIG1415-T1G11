#include "Animation.h"

Animation::Animation(long st, long d):startingTime(st*1000),endingTime((st+d)*1000),duration(d*1000), state(0), time(0)
{
	
}

Animation::~Animation(void)
{
}


unsigned Animation::getEndTime() const {
	return endingTime;
}


bool Animation::complete() const{
	return state == 2;
}
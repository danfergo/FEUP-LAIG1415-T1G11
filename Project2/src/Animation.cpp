#include "Animation.h"

Animation::Animation(long st, long d):startingTime(st*1000),endingTime((st+d)*1000),duration(d*1000)
{
	
}

Animation::~Animation(void)
{
}


unsigned Animation::getEndTime() const {
	return endingTime;
}

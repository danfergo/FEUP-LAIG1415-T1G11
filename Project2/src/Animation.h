#pragma once
class Animation
{
protected:
	long startingTime;
	long duration;
public:
	Animation(long startTime,long duration);
	virtual ~Animation();
	virtual void animate(long time) const = 0;
};


#pragma once
class Animation
{
protected:
	long startingTime,endingTime;
	long duration;
public:
	Animation(long startTime,long duration);
	virtual ~Animation();
	virtual void animate() const = 0;
	virtual void update(unsigned long time) = 0;
	virtual Animation * clone(unsigned newStartTime) = 0;
	long getDuration() const;
	unsigned getEndTime() const;
};

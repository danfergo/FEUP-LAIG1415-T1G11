#pragma once
class Animation
{
protected:
	unsigned long startingTime,endingTime, time;
	long duration;
	int state;
public:
	Animation(long startTime,long duration);
	virtual ~Animation();
	virtual void animate() const = 0;
	virtual void update(unsigned long ticks) = 0;
	virtual Animation * clone(unsigned newStartTime) = 0;
	long getDuration() const;
	unsigned getEndTime() const;
	bool complete() const;
	virtual void getTransformationMatrix(float * ) const = 0;
};

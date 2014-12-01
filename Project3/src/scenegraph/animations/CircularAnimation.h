#pragma once
#include "Animation.h"
#include "scenegraph\utils\Point.h"

class CircularAnimation: public Animation
{
private:
	Point3d center, currentPosition,endPosition;
	float radius, startAngle,endAngle,currentAngle,endPositionAngle;
	double angularVelocity;
public:
	CircularAnimation(long startingTime,long duration, Point3d center, float radius, float startAngle,float endAngle);
	virtual void animate() const;
	virtual void update(unsigned long time);
	virtual Animation * clone(unsigned newStartTime);
};


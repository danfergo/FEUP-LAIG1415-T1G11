#pragma once
#include "Animation.h"
#include "scenegraph/utils/Point.h"
#include <vector>
class LinearAnimation: public Animation
{
private:
	std::vector<Point3d> controlPoints;
	std::vector<Vector3d> directions;
	float pointPercentage;
public:
	LinearAnimation(long startingTime, long duration);
	void animate(long time);
	void addControlPoint(Point3d point);
	~LinearAnimation(void);
};


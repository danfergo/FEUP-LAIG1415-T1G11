#pragma once
#include "Animation.h"
#include "../utils/Point.h"
#include <vector>
class LinearAnimation: public Animation
{
private:
	std::vector<Point3d> controlPoints;
	std::vector<Vector3d> directions;
	std::vector<double> milestones;
	int currentPositionIndex;
	Point3d currentPosition,lastPosition;
	bool directional;
	double currentAngleDirectionXZ,lastAngleDirectionXZ;
public:
	LinearAnimation(long startingTime, long duration);
	LinearAnimation(long startingTime, long duration, bool dir);
	void animate() const;
	void update(unsigned long time);
	void addControlPoint(Point3d point);
	void calcMilestones();
	virtual Animation * clone(unsigned newStartTime);
	void getTransformationMatrix(float *) const;
	~LinearAnimation(void);
};


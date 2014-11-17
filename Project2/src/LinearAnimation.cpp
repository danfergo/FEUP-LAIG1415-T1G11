#include "LinearAnimation.h"
#include "scenegraph/utils/Normals.h"


LinearAnimation::LinearAnimation(long startingTime, long duration):Animation(startingTime,duration)
{


}

void LinearAnimation::addControlPoint(Point3d point){
	controlPoints.push_back(point);
	if(this->controlPoints.size() > 1){
		Point3d last = controlPoints[controlPoints.size()-1];		
		Point3d penultimate = controlPoints[controlPoints.size()-2];
		Vector3d direction = {last.x - penultimate.x , last.y - penultimate.y ,  last.z - penultimate.z};
		normals::normalizeVector(direction);
		directions.push_back(direction);
		pointPercentage =  (float)1 /(float)controlPoints.size();
	}
}


void LinearAnimation::animate(long time){
	long aux = time - startingTime;
	if(aux >= 0 && aux <= duration){
		int controlPoint = floor(
		
	
	}
}


LinearAnimation::~LinearAnimation(void)
{
}

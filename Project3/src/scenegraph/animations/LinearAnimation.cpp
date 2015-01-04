#include "LinearAnimation.h"
#include "../utils/Normals.h"
#include "CGFobject.h"
#include <math.h>
#include <limits>
#include <iostream>


static float const PI = acos(-1.0);

LinearAnimation::LinearAnimation(long startingTime, long duration):Animation(startingTime,duration),currentPositionIndex(0), directional(true)
{
	currentAngleDirectionXZ = 0;

	currentPosition.x = 0;
	currentPosition.y = 0;
	currentPosition.z = 0;
}

LinearAnimation::LinearAnimation(long startingTime, long duration, bool dir):Animation(startingTime,duration),currentPositionIndex(0), directional(dir){

}


void LinearAnimation::addControlPoint(Point3d point){
	controlPoints.push_back(point);
	if(this->controlPoints.size() > 1){
		Point3d last = controlPoints[controlPoints.size()-1];		
		Point3d penultimate = controlPoints[controlPoints.size()-2];
		Vector3d direction = {last.x - penultimate.x , last.y - penultimate.y ,  last.z - penultimate.z};
		directions.push_back(direction);
	}
}

void LinearAnimation::calcMilestones(){
	std::vector<Vector3d>::iterator it = directions.begin();
	double velocity=0, lastmilestone = (double)startingTime;
	for(; it < directions.end(); it++){
		velocity += normals::norm(*it);
	}
	velocity /= duration;	
	
	milestones.push_back(lastmilestone);
	for(it = directions.begin(); it < directions.end(); it++){
		lastmilestone += normals::norm(*it)/(double)velocity;
		milestones.push_back(lastmilestone);
	}


	lastPosition = controlPoints.back();
	Point2d groundDirProjection = {directions.back().x,directions.back().z};
	normals::normalizeVector(groundDirProjection);
		
	/** using y because Point2d is (x,y) istead of (x,z),
	* sets currentAngleDirectionXZ as the angle between Z axis and 
	* the projection in XZ of direction vector, in dregrees. **/
	if(groundDirProjection.y >= 0){
		this->lastAngleDirectionXZ =  (180*asin(groundDirProjection.x)/PI);
	}else{
		this->lastAngleDirectionXZ =  180 - (180*asin(groundDirProjection.x)/PI);
	}
}


void LinearAnimation::animate() const{
	glTranslated(currentPosition.x,currentPosition.y,currentPosition.z);
	if(directional)glRotated(currentAngleDirectionXZ,0,1,0);
}


void LinearAnimation::update(unsigned long ticks){
	if(state == 0){
		state = 1;
		calcMilestones();
	}
	time += ticks;

	if(time >= startingTime && time < endingTime){
		unsigned long nextPosTime = milestones[currentPositionIndex+1];;
		while(time >= nextPosTime){ // switches to next controlpoint, prevents uge lag case.
			currentPositionIndex++;
			nextPosTime =  milestones[currentPositionIndex+1];
		} 
		long currPosTime = milestones[currentPositionIndex];
		Vector3d * currNextDirection = &directions[currentPositionIndex];
		Point3d * currPosition = &this->controlPoints[currentPositionIndex];
		float progress = (time - currPosTime)/(float)(nextPosTime-currPosTime);

		this->currentPosition.x = progress*currNextDirection->x + currPosition->x;
		this->currentPosition.y = progress*currNextDirection->y + currPosition->y;
		this->currentPosition.z = progress*currNextDirection->z + currPosition->z;

		Point2d groundDirProjection = {currNextDirection->x,currNextDirection->z};
		normals::normalizeVector(groundDirProjection);
		
		/** using y because Point2d is (x,y) istead of (x,z),
		* sets currentAngleDirectionXZ as the angle between Z axis and 
		* the projection in XZ of direction vector, in dregrees. **/
		if(groundDirProjection.y >= 0){
			this->currentAngleDirectionXZ =  (180*asin(groundDirProjection.x)/PI);
		}else{
			this->currentAngleDirectionXZ =  180 - (180*asin(groundDirProjection.x)/PI);
		}
		
	}else if(time >= endingTime){
			currentPositionIndex = 0;
			currentAngleDirectionXZ = lastAngleDirectionXZ;
			currentPosition = lastPosition;
			state = 2;
	}

}

Animation * LinearAnimation::clone(unsigned newStartTime){
	LinearAnimation * animation = new LinearAnimation(newStartTime/1000, this->duration/1000);
	for(std::vector<Point3d>::iterator it = controlPoints.begin(); it != controlPoints.end(); it++ ){
		animation->addControlPoint(*it);
	}
	animation->calcMilestones();
	return animation;
}

void LinearAnimation::getTransformationMatrix(float * matrix) const{
	float temp[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, temp);
		glLoadIdentity();
		glTranslated(currentPosition.x,currentPosition.y,currentPosition.z);
		if(directional)glRotated(currentAngleDirectionXZ,0,1,0);
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	glLoadMatrixf(temp);
}




LinearAnimation::~LinearAnimation(void)
{
}

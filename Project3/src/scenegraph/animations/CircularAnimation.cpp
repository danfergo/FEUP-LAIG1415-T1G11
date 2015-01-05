#include "CircularAnimation.h"
#include <math.h>
#include "CGFobject.h"

static float const PI = acos(-1.0);

CircularAnimation::CircularAnimation(long st,long dur, Point3d center, float radius, float startAngle,float endAngle):
Animation(st,dur), center(center), radius(radius),startAngle(startAngle),endAngle(endAngle)
{
	angularVelocity = (endAngle - startAngle)/(double)duration;
	currentPosition.x = 0;
	currentPosition.y = 0;
	currentPosition.z = 0;
	currentAngle = 0;


	double endAngleRad = PI*(double)endAngle/180;
	endPosition.x = center.x + radius*sin(endAngleRad);
	endPosition.y = center.y;
	endPosition.z = center.z + radius*cos(endAngleRad);
	this->endPositionAngle = endAngle; // + 90;
}


void CircularAnimation::animate() const{
	glTranslated(currentPosition.x,currentPosition.y,currentPosition.z);
	glRotated(currentAngle,0,1,0);
}


void CircularAnimation::update(unsigned long ticks){
	time += ticks;

	if(time >= startingTime && time <= endingTime){
		double currentAngleDeg = fmod(startAngle + angularVelocity*(time-startingTime),(double)360);
		double currentAngleRad = (PI*(double)currentAngleDeg)/180;
		currentPosition.x = center.x + radius*sin(currentAngleRad);
		currentPosition.y = center.y;
		currentPosition.z = center.z + radius*cos(currentAngleRad);
		this->currentAngle = currentAngleDeg; // + 90;**/
	}else if(time > endingTime){
		this->currentPosition = endPosition;
		this->currentAngle = endPositionAngle;
		state = 2;
	}
}

Animation * CircularAnimation::clone(unsigned newStartTime){
	return new CircularAnimation(newStartTime/1000,this->duration/1000,this->center,this->radius,this->startAngle,this->endAngle);
}

void CircularAnimation::getTransformationMatrix(float * matrix) const{
	float temp[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, temp);
		glLoadIdentity();
		glTranslated(currentPosition.x,currentPosition.y,currentPosition.z);
		glRotated(currentAngle,0,1,0);
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	glLoadMatrixf(temp);
}


Point3d CircularAnimation::getCurrentPosition(){
	return this->currentPosition;
}
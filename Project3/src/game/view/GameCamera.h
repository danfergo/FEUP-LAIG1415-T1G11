#pragma once
#include "../../scenegraph/Camera.h"
#include "../../scenegraph/animations/CircularAnimation.h"

class GameCamera: public CameraPerspective
{
private:
	CircularAnimation * animation;
	Point3d calcTarget();
public: 
	GameCamera(std::string title,float near, float far, float pos[3], float target[3],float angle);
	void produceRotation(float angle,int dur);
	void update(unsigned long ticks);

	~GameCamera(void);
};


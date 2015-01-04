#ifndef CAMERA_H_F_
#define CAMERA_H_F_

#include "CGFcamera.h"
#include <string>

class Camera: public CGFcamera{
protected:
	std::string title;
	float near,far;
public:
	Camera(std::string title): CGFcamera(), title(title){};
	Camera(std::string title, float near, float far);
	std::string getTitle() const;
	virtual void update(unsigned long ticks){};
};

class CameraOrtho: public Camera
{
public:
	typedef enum Axis{XX,YY,ZZ} Axis;
private:
	float left, right, top, bottom;
	Axis axis;
public:
	CameraOrtho(std::string title, float near, float far, float left, float right,float bottom, float top, Axis axis);
	virtual void applyView();
	virtual void updateProjectionMatrix(int width, int height);
	
};


class CameraPerspective: public Camera{
protected:
	float targ[3],pos[3];
	float angle,aspectRatio;
public:
	CameraPerspective(std::string title,float near, float far, float pos[3], float target[3],float angle);
	virtual void applyView();
	virtual void updateProjectionMatrix(int width, int height);
 };

#endif


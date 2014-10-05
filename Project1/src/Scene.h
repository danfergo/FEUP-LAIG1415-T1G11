#ifndef SCENE_H
#define SCENE_H

#include "CGFscene.h"
#include "scenegraph/Node.h"
#include "Light.h"

class Scene : public CGFscene
{
private:
	Node * root;
	std::vector<Light*> lights;
public:
	static enum ShaddingMode{FLAT,GOURAUD};
	static enum DrawingMode{FILL,LINE,POINT};
	static enum CullingFace{NONE,BACK,FRONT,BOTH};
	static enum DrawingOrder{CCW,CW};

	ShaddingMode shaddingMode;
	DrawingMode drawingMode;  // applyed
	CullingFace cullingFace;  // applyed
	DrawingOrder drawingOrder; // applyed
	float backgroundColor[4]; // applyed
	float ambientLight[4]; // applyed
	bool lightingEnabled; // applyed
	bool doublesidedEnabled; // applyed
	bool localIlluminationEnabled;

	Scene();
	void init();
	void display();
	void setRoot(Node * root);
	bool addLight(float aa[4],float dd[4],float ss[4],bool enabled, 
		float location[4], bool visible,float angle=-1, float exponent=-1,float target[4] = NULL);

	void setShaddingMode(ShaddingMode shaddingMode);
	void setDrawingMode(DrawingMode drawingMode);
	void setCullingFace(CullingFace cullingFace);
	void setDrawingOrder(DrawingOrder drawingOrder);
	void setBackgroundColor(float backgroundColor[4]);
	void setAmbientLight(float ambientLight[4]);
	void setLightingEnabled(bool lightingEnabled);
	void setDoubleSidedEnabled(bool doublesidedEnabled);
	void setLocalIlluminationEnabled(bool localIlliuminationEnabled);


}; 

#endif
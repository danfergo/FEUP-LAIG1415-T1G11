#ifndef SCENE_H
#define SCENE_H

#include "CGFscene.h"
#include "scenegraph/Node.h"

class Scene : public CGFscene
{
private:
	Node * root;
public:
	static enum ShaddingMode{FLAT,GOURAUD};
	static enum DrawingMode{FILL,LINE,POINT};
	static enum CullingFace{NONE,BACK,FRONT,BOTH};
	static enum DrawingOrder{CCW,CW};

	ShaddingMode shaddingMode;
	DrawingMode drawingMode;
	CullingFace cullingFace;
	DrawingOrder drawingOrder;
	float backgroundColor[4];
	float ambientLight[4];
	bool lightingEnabled;
	bool doublesidedEnabled;
	bool localIlluminationEnabled;

	Scene();
	void init();
	void display();
	void setRoot(Node * root);

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
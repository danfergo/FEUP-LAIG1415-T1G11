#pragma once


#include "../scenegraph/Point.h"
#include "../scenegraph/Triangle.h"
#include "../Scene.h"
#include "tinyxml.h"
#include "CGFobject.h"


class ParseANFscene{
private:
	static Node * parseGraph(TiXmlElement * anfGraph);
	static Node * parseNode(TiXmlElement * anfNode);
	static CGFobject * parseTriangle(TiXmlElement * anfTriangle);

public:
	static bool parse(Scene * scene,const char* filename);

};



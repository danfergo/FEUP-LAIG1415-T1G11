#pragma once
	
#include "../Scene.h"
#include "tinyxml.h"


class ParseANFscene{
private:
	static Scene * scene;
	static bool parseGraph(TiXmlElement * anfGraph);
	static bool parseNode(TiXmlElement * anfNode);
	static bool parseTriangle(TiXmlElement * anfTriangle);

public:
	static bool parse(Scene * scene,const char* filename);

};



#pragma once

#include <map>

#include "../scenegraph/Point.h"
#include "../scenegraph/Triangle.h"
#include "../Scene.h"
#include "tinyxml.h"
#include "CGFobject.h"
#include <vector>
#include <string>



class ParseANFscene{
private:
	typedef struct NodeWrapper{
		Node * node;
		std::vector<std::string> descendants;
		int indegree;
	} NodeWrapper;
	
	char parseMode;
	std::map<std::string,CGFobject* (*)(TiXmlElement *)> subParsers;

	Node * parseGraph(TiXmlElement * anfGraph);
	NodeWrapper ParseANFscene::parseNode(TiXmlElement * anfNode);
	static CGFobject * parseTriangle(TiXmlElement * anfTriangle);
	bool parseTransforms(Node * node, TiXmlElement * anfTransforms);
	bool buildSceneGraph(std::string root, map<std::string, NodeWrapper> & nodes);
public:
	const static char STRICT;
	const static char PERMISSIVE;
	const static char SILENT;
	bool parse(Scene * scene,const char* filename);
	ParseANFscene(const char parseMode);
};



#pragma once

#include <map>

#include "../scenegraph/Point.h"
#include "../scenegraph/Triangle.h"
#include "../Scene.h"
#include "tinyxml.h"
#include "CGFobject.h"
#include "CGFappearance.h"
#include <vector>
#include <string>



class ParseANFscene{

private:
	typedef CGFobject* (ParseANFscene::*PrimitiveParser)(TiXmlElement *);

	class ParseExep{ 
	};


	typedef struct AppearanceWrapper{
		CGFappearance * appearance;
		bool used;
	} AppearanceWrapper;

	typedef struct TextureWrapper{
		std::string string;
		bool used;
	} TextureWrapper;

	typedef struct NodeWrapper{
		Node * node;
		std::vector<std::string> descendants;
		int indegree;
	} NodeWrapper;
	
	char parseMode;
	std::map<std::string,PrimitiveParser> subParsers;

	Node * parseGraph(TiXmlElement * anfGraph);
	bool parseAppearances(TiXmlElement * anfAppearances, std::map<std::string, CGFappearance *> & appearances);
	CGFappearance * parseAppearance(TiXmlElement * anfAppearance);
	NodeWrapper parseNode(TiXmlElement * anfNode);
	CGFobject * parseTriangle(TiXmlElement * anfTriangle);
	bool parseTransforms(Node * node, TiXmlElement * anfTransforms);
	bool buildSceneGraph(std::string root, map<std::string, NodeWrapper> & nodes);
	void initPrimitiveParsers();
 

	const static char WARNING;
	const static char ERROR;
	static std::string str(const char * str);
	void issue(std::string err, const char flag);
public:

	const static char STRICT;
	const static char PERMISSIVE;
	const static char SILENT;
	bool parse(Scene * scene,const char* filename);
	ParseANFscene(const char parseMode);
};



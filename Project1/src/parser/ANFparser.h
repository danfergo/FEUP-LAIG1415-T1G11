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
	typedef CGFobject* (ParseANFscene::*PrimitiveParser)(TiXmlElement *);
	std::map<std::string,PrimitiveParser> subParsers;

	CGFobject * parseTriangle(TiXmlElement * anfTriangle);
	void initPrimitiveParsers();

	bool parseTransforms(Node * node, TiXmlElement * anfTransforms);
	NodeWrapper parseNode(TiXmlElement * anfNode);
	bool buildSceneGraph(std::string root, map<std::string, NodeWrapper> & nodes);

	CGFappearance * parseAppearance(TiXmlElement * anfAppearance);
	void parseAppearances(TiXmlElement * anfAppearances, std::map<std::string, CGFappearance *> & appearances);

 
	const static char WARNING;
	const static char ERROR;
	static std::string str(const char * str);
	void issue(std::string err, const char flag);

	Node * parseGraph(TiXmlElement * anfGraph);
public:

	const static char STRICT;
	const static char PERMISSIVE;
	const static char SILENT;
	bool parse(Scene * scene,const char* filename);
	ParseANFscene(const char parseMode);
};



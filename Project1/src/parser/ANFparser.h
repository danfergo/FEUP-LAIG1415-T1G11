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



class ANFparser{

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
	typedef CGFobject* (ANFparser::*PrimitiveParser)(TiXmlElement *);
	std::map<std::string,PrimitiveParser> subParsers;
	CGFobject * parseTriangle(TiXmlElement * anfTriangle);
	void initPrimitiveParsers();

	
	NodeWrapper parseNode(TiXmlElement * anfNode,std::map<std::string, CGFappearance *> & appearances);
	Node * parseGraph(TiXmlElement * anfGraph,std::map<std::string, CGFappearance *> & appearances);
	bool parseTransforms(Node * node, TiXmlElement * anfTransforms);
	bool buildSceneGraph(std::string root, map<std::string, NodeWrapper> & nodes);

	CGFappearance * parseAppearance(TiXmlElement * anfAppearance);
	void parseAppearances(TiXmlElement * anfAppearances, std::map<std::string, CGFappearance *> & appearances);
	
	void parseGlobals(TiXmlElement * anfGlobals);
	void parseGlobalsDrawing(TiXmlElement * anfDrawing);
	void parseGlobalsCulling(TiXmlElement * anfCulling);
	void parseGlobalsLighting(TiXmlElement * anfLighting);
 
	const static char WARNING;
	const static char ERROR;
	static std::string str(const char * str);
	void issue(std::string err, const char flag);

	Scene * scene;
public:

	const static char STRICT;
	const static char PERMISSIVE;
	const static char SILENT;
	bool parse(Scene * scene,const char* filename);
	ANFparser(const char parseMode);
};



#ifndef ANF_PARSER_F_H
#define ANF_PARSER_F_H

#include <map>

#include "../scenegraph/Point.h"
#include "../scenegraph/Triangle.h"
#include "../Scene.h"
#include "../Light.h"
#include "../scenegraph/Texture.h"
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

	//Graph
	NodeWrapper parseNode(TiXmlElement * anfNode,std::map<std::string, CGFappearance *> & appearances);
	Node * parseGraph(TiXmlElement * anfGraph,std::map<std::string, CGFappearance *> & appearances);
	bool parseTransforms(Node * node, TiXmlElement * anfTransforms);
	bool buildSceneGraph(std::string root, map<std::string, NodeWrapper> & nodes);

	//Appearances
	CGFappearance * parseAppearance(TiXmlElement * anfAppearance,std::map<std::string, Texture *> & textures);
	void parseAppearances(TiXmlElement * anfAppearances, std::map<std::string, CGFappearance *> & appearances,
		std::map<std::string, Texture *> & textures);
	void parseComponent(TiXmlElement * anfParent, float aa[4], float dd[4], float ss[4]);

	//Textures
	Texture * parseTexture(TiXmlElement * anfTexture);
	void parseTextures(TiXmlElement * anfTextures, map<std::string,Texture *> & textures);

	//Lights
	void parseLights(TiXmlElement * anfLights);
	void parseLight(TiXmlElement * anfLight);
	
	//Globals
	void parseGlobals(TiXmlElement * anfGlobals);
	void parseGlobalsDrawing(TiXmlElement * anfDrawing);
	void parseGlobalsCulling(TiXmlElement * anfCulling);
	void parseGlobalsLighting(TiXmlElement * anfLighting);
 
	//Error handling
	const static char WARNING;
	const static char ERROR;
	void issue(std::string err, const char flag);

	//safe char* -> std::string
	static std::string str(const char * str);

	Scene * scene;
public:
	const static char STRICT;
	const static char PERMISSIVE;
	const static char SILENT;
	ANFparser(const char parseMode);
	bool parse(Scene * scene,const char* filename);
};

#endif


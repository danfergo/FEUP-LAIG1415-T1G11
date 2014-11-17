#ifndef ANF_PARSER_F_H
#define ANF_PARSER_F_H

#include <map>

#include "../scenegraph/utils/Point.h"
#include "../scenegraph/Scene.h"
#include "../scenegraph/Light.h"
#include "../scenegraph/Texture.h"
#include "tinyxml.h"
#include "../scenegraph/Primitive.h"
#include "../scenegraph/Appearance.h"
#include "../scenegraph/Camera.h"
#include <vector>
#include <string>


class ANFparser{

private:
	class ParseExep{ 
	};

	typedef struct AppearanceWrapper{
		Appearance * appearance;
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
	typedef Primitive* (ANFparser::*PrimitiveParser)(TiXmlElement *);
	std::map<std::string,PrimitiveParser> subParsers;
	Primitive * parseTriangle(TiXmlElement * anfTriangle);
	Primitive * parseSphere(TiXmlElement * anfSphere);
	Primitive * parseToro(TiXmlElement * anfToro);
	Primitive * parseCylinder(TiXmlElement * anfCylinder);
	Primitive * parseRetangle(TiXmlElement * anfRetangle);
	Primitive * parsePatch(TiXmlElement * anfPatch);
	void initPrimitiveParsers();

	//Cameras
	void parseCameras(TiXmlElement *anfCameras,std::string initialCamera);
	Camera * parseCameraOrtho(TiXmlElement *anfCamera);
	Camera * parseCameraPrespective(TiXmlElement *anfCamera);

	//Graph
	NodeWrapper parseNode(TiXmlElement * anfNode,std::map<std::string, Appearance *> & appearances);
	Node * parseGraph(TiXmlElement * anfGraph,std::map<std::string, Appearance *> & appearances);
	bool parseTransforms(Node * node, TiXmlElement * anfTransforms);
	bool buildSceneGraph(std::string root, map<std::string, NodeWrapper> & nodes);

	//Appearances
	Appearance * parseAppearance(TiXmlElement * anfAppearance,std::map<std::string, Texture *> & textures);
	void parseAppearances(TiXmlElement * anfAppearances, std::map<std::string, Appearance *> & appearances,
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
 
	//Cameras 
	//void parseCameras(TiXmlElement * anfCameras);
	//CameraOrtho * parseCameraOrtho(TiXmlElement * anfCamera);
	//CameraPrespective * parseCameraPrespective(TiXmlElement * anfCamera);

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


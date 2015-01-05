#ifndef ANF_PARSER_F_H
#define ANF_PARSER_F_H

#include <map>

#include "../utils/Point.h"
#include "../Scene.h"
#include "../Light.h"
#include "../appearances/Texture.h"
#include "tinyxml.h"
#include "../primitives/Primitive.h"
#include "../appearances/Appearance.h"
#include "../Camera.h"
#include "../animations/LinearAnimation.h"
#include "../animations/CircularAnimation.h"
#include <vector>
#include <string>

#include "../../game/view/Board.h"
#include "../../game/view/MenuButton.h"

class MenuButton;

class ParseExep{ 
};

class ANFparser{
public:
	static Board * boardFound;
	static MenuButton * buttonFound0;
	static MenuButton * buttonFound1;
	static MenuButton * buttonFound2;
	static MenuButton * buttonFound3;
	static Node  * pieceModelFound;
private:


	

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

		
	/** PROJECT 2 - new primitives **/
	Primitive * parsePlane(TiXmlElement * anfPlane);
	Primitive * parsePatch(TiXmlElement * anfPatch);
	Primitive * parseFlag(TiXmlElement * anfFlag);
	Primitive * parseVehicle(TiXmlElement * anfVehicle);

	void initPrimitiveParsers();

	/** Animations **/ 
	Animation * parseAnimation(TiXmlElement * anfAnimation);
	void parseAnimations(TiXmlElement * anfAnimations, map<std::string,Animation *> & animations);

	/** Cameras **/
	void parseCameras(TiXmlElement *anfCameras,std::string initialCamera);
	Camera * parseCameraOrtho(TiXmlElement *anfCamera);
	Camera * parseCameraPrespective(TiXmlElement *anfCamera);

	/** Graph **/
	NodeWrapper parseNode(TiXmlElement * anfNode,std::map<std::string, Appearance *> & appearances, std::map<std::string, Animation *> & animations);
	Node * parseGraph(TiXmlElement * anfGraph,std::map<std::string, Appearance *> & appearances, std::map<std::string, Animation *> & animations);
	bool parseTransforms(Node * node, TiXmlElement * anfTransforms);
	bool buildSceneGraph(std::string root, map<std::string, NodeWrapper> & nodes);

	/** Appearances **/
	Appearance * parseAppearance(TiXmlElement * anfAppearance,std::map<std::string, Texture *> & textures);
	void parseAppearances(TiXmlElement * anfAppearances, std::map<std::string, Appearance *> & appearances,
	std::map<std::string, Texture *> & textures);
	void parseComponent(TiXmlElement * anfParent, float aa[4], float dd[4], float ss[4]);

	/** Textures **/
	Texture * parseTexture(TiXmlElement * anfTexture);
	void parseTextures(TiXmlElement * anfTextures, map<std::string,Texture *> & textures);

	/** Lights **/
	void parseLights(TiXmlElement * anfLights);
	void parseLight(TiXmlElement * anfLight);
	
	/* Globals */
	void parseGlobals(TiXmlElement * anfGlobals);
	void parseGlobalsDrawing(TiXmlElement * anfDrawing);
	void parseGlobalsCulling(TiXmlElement * anfCulling);
	void parseGlobalsLighting(TiXmlElement * anfLighting);
 

	/* Error handling */
	const static char WARNING,ERR;
	void issue(std::string err, const char flag);

	static std::string str(const char * str);

	Scene * scene;
public:
	const static char STRIC, PERMISSIVE,SILENT;
	ANFparser(const char parseMode);
	bool parse(Scene * scene,const char* filename);
};

#endif


#include "ANFparser.h"
#include <iostream>
#include <map>


const char ANFparser::STRICT = 0;
const char ANFparser::PERMISSIVE = 1;
const char ANFparser::SILENT = 2;

const char ANFparser::WARNING = 0;
const char ANFparser::ERROR = 1;

ANFparser::ANFparser(const char parseMode): parseMode(parseMode){
	initPrimitiveParsers();
}

bool ANFparser::parse(Scene * scene,const char* filename){
	this->scene = scene;

	try{
		TiXmlDocument * doc = new TiXmlDocument(filename);

		//First things first, reading the XML/ANF file
		if (!doc->LoadFile()){
			issue("Could not load file '%"+str(filename)+"'. Error='" + str(doc->ErrorDesc()) + "'.", ERROR);
		}

		//Must exist anf root block
		TiXmlElement* anfRoot = doc->FirstChildElement("anf");
		if (!anfRoot){
			issue("Main block 'anf' block not found!",ERROR);
		}

		//Lets process the global variables
		TiXmlElement* anfGlobals = anfRoot->FirstChildElement("globals");
		if(!anfGlobals){
			issue("Block 'globals' not found!",WARNING);
		}else{
			parseGlobals(anfGlobals);
		}
		
		//Lets process the cameras
		TiXmlElement* anfCameras = anfRoot->FirstChildElement("cameras");
		if(!anfCameras){
			issue("Block 'cameras' not found!",ERROR);
		}else{
			std::string firstCameraId = str(anfCameras->Attribute("initial"));
			if(firstCameraId == "" ){
				issue("Cameras block must declare the first camera.. ", WARNING);
			}
			parseCameras(anfCameras,firstCameraId);
		}

		//Lets process the lights
		TiXmlElement* anfLights = anfRoot->FirstChildElement("lights");
		if(!anfLights){
			issue("Block 'lights' not found!",WARNING);
		}else{
			parseLights(anfLights);
		}

		//If textures extist, we process it
		TiXmlElement* anfTextures = anfRoot->FirstChildElement("textures");
		map<std::string,Texture *> textures;
		if(!anfTextures){
			issue("Block 'textures' not found!",WARNING);
		}else{
			parseTextures(anfTextures,textures);
		}


		//If appearances block exist, we call its parser
		TiXmlElement* anfAppearances = anfRoot->FirstChildElement("appearances");
		map<std::string,Appearance *> appearances;
		if(!anfAppearances){
			issue("Block 'appearances' not found!",WARNING);
		}else{
			parseAppearances(anfAppearances,appearances,textures);
		}
		

		//If graph block exist, we call its parser
		TiXmlElement* anfGraph = anfRoot->FirstChildElement("graph");
		if(!anfGraph){
			issue("Block 'graph' not found!",ERROR);
		}else{
			this->scene->setRoot(parseGraph(anfGraph,appearances));
		}

		return true; 
	}catch(...){
		return false;
	}
}

std::string ANFparser::str(const char * str){
	return std::string(str == NULL ? "" : str);
}

void ANFparser::issue(std::string err, const char flag) {
	std::string prefix = (flag == ERROR)? " ERROR! " : " WARNING! "; 
	std::cout << prefix << err << std::endl;
	if(flag == ERROR || (parseMode == STRICT)) throw ParseExep();
}; 
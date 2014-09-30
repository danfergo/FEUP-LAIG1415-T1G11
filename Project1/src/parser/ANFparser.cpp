#include "ANFparser.h"
#include <iostream>
#include <map>


const char ParseANFscene::STRICT = 0;
const char ParseANFscene::PERMISSIVE = 1;
const char ParseANFscene::SILENT = 2;

const char ParseANFscene::WARNING = 0;
const char ParseANFscene::ERROR = 1;

ParseANFscene::ParseANFscene(const char parseMode): parseMode(parseMode){
	initPrimitiveParsers();
}

bool ParseANFscene::parse(Scene * scene,const char* filename){
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
		/*
		//If appearances block exist, we call its parser
		TiXmlElement* anfAppearances = anfRoot->FirstChildElement("appearances");
		map<std::string,CGFappearance *> appearances;
		if(!anfAppearances){
			issue("Block 'appearances' not found! \n");
		}else{
			parseAppearances(anfAppearances,appearances);
		}
		*/
		//If graph block exist, we call its parser
		TiXmlElement* anfGraph = anfRoot->FirstChildElement("graph");
		if(!anfGraph){
			issue("Block 'graph' not found!",ERROR);
		}else{
			scene->setRoot(parseGraph(anfGraph));
		}
		return true; 
	}catch(...){
		return false;
	}
}

std::string ParseANFscene::str(const char * str){
	return std::string(str == NULL ? "" : str);
}

void ParseANFscene::issue(std::string err, const char flag) {
	std::string prefix = (flag == ERROR)? "ERROR! " : "WARNING! "; 
	std::cout << prefix << err << std::endl;
	if(flag == ERROR) throw ParseExep();
}; 
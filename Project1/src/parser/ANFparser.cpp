#include "ANFparser.h"
#include <string>
#include <iostream>


#include "../scenegraph/Point.h"
#include "../scenegraph/Triangle.h"

Scene* ParseANFscene::scene = NULL;


bool ParseANFscene::parse(Scene * scene,const char* filename){
	ParseANFscene::scene = scene;
	TiXmlDocument * doc = new TiXmlDocument(filename);

	scene->root = new Node();

	if (!doc->LoadFile()){
		printf("ERROR! Could not load file '%s'. Error='%s'.", filename, doc->ErrorDesc());
		return false;
	}

	TiXmlElement* anfRoot = doc->FirstChildElement("anf");
	if (anfRoot == NULL){
		printf("ERROR! Main 'anf' block not found! \n");
		return false;
	}


	TiXmlElement* anfGraph = anfRoot->FirstChildElement("graph");
	if(anfGraph == NULL){
		printf("ERROR! Block 'graph' not found! \n");
		return false;
	}else{
		if(!parseGraph(anfGraph)){
			return false;
		}
	}


	return true;
}


bool ParseANFscene::parseGraph(TiXmlElement * anfGraph){

	TiXmlElement *node = anfGraph->FirstChildElement();

	while(node){
		if(!parseNode(node)){
			return false;
		}
		node=node->NextSiblingElement();
	}

	return true;
}


bool ParseANFscene::parseNode(TiXmlElement * anfNode){


	// Lets Parse node primitives
	TiXmlElement * primitives = anfNode->FirstChildElement("primitives");
	if (primitives == NULL){
		printf("ERROR! Primitives block not found! \n");
		return false;
	}else{
		TiXmlElement * primitive = primitives->FirstChildElement();
		while(primitive){
			if(string(primitive->Value()) ==  "triangle"){
				if(!parseTriangle(primitive)) return false;
			}else{
				printf("ERROR! Invalid primitive found! \n");
			}
			primitive=primitive->NextSiblingElement();
		}
	}
	return true;
}

bool ParseANFscene::parseTriangle(TiXmlElement * anfTriangle){
	char *valString;

	Point3d data[3] = {{0,0,0},{0,0,0},{0,0,0}};

	for(unsigned i = 0; i < 3; i++){

		std::string attr = "xyz" + std::to_string((long double)(i+1));
		valString=(char *) anfTriangle->Attribute(attr.c_str());
		if(!valString || !sscanf(valString,"%f %f %f",&data[i].x, &data[i].y, &data[i].z)==3){

			printf("Error! error parsing xyz%d \n",i+1);
			return false;
		}
	}
	
	scene->root->addPrimitive(new Triangle(data));
	return true;
}
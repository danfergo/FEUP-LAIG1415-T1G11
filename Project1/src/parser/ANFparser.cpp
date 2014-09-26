#include "ANFparser.h"
#include <string>
#include <iostream>
#include <map>


bool ParseANFscene::parse(Scene * scene,const char* filename){

	TiXmlDocument * doc = new TiXmlDocument(filename);


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
		Node * root = parseGraph(anfGraph);
		if(root != NULL){
			scene->setRoot(root);
		}
	}

	return true;
}


Node * ParseANFscene::parseGraph(TiXmlElement * anfGraph){

	TiXmlElement *node = anfGraph->FirstChildElement();

	while(node){        // draft code. must be improved. only supporting one good node.
		return parseNode(node);

		node=node->NextSiblingElement();
	}

	return NULL;
}


Node * ParseANFscene::parseNode(TiXmlElement * anfNode){
	std::map<std::string,CGFobject* (*)(TiXmlElement *)> subParsers;
	
	//insert primitive parsers here
	//subParsers.insert(std::pair<string,Triangle* (*)(TiXmlElement *)>("triangle",ParseANFscene::parseTriangle));

	Node * root = new Node();
		
/*
	// Lets Parse node primitives
	TiXmlElement * primitives = anfNode->FirstChildElement("primitives");
	if (primitives == NULL){
		printf("ERROR! Primitives block not found! \n");
		return NULL;
	}else{
		TiXmlElement * primitive = primitives->FirstChildElement();                 // draft algorithm must be improved. safty issues
		while(primitive){
			try{
				root->addPrimitive(subParsers.at(primitive->Value())(primitive));
			}catch(...){
				printf("ERROR! Invalid primitive '%s' found! \n",primitive->Value());
			}

			primitive=primitive->NextSiblingElement();
		}
	}`*/
	return root;
}

Triangle * ParseANFscene::parseTriangle(TiXmlElement * anfTriangle){
	char *valString;

	Point3d data[3] = {{0,0,0},{0,0,0},{0,0,0}};

	for(unsigned i = 0; i < 3; i++){

		std::string attr = "xyz" + std::to_string((long double)(i+1));
		valString=(char *) anfTriangle->Attribute(attr.c_str());
		if(!valString || !sscanf(valString,"%f %f %f",&data[i].x, &data[i].y, &data[i].z)==3){

			printf("Error! error parsing xyz%d \n",i+1);
			return NULL;
		}
	}
	
	return new Triangle(data);
}
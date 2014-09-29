#include "ANFparser.h"
#include <iostream>
#include <map>
#include <queue>


void ParseANFscene::initPrimitiveParsers(){
	
	//insert here all the primitive's parser funcition
	subParsers.insert(std::pair<std::string,CGFobject* (*)(TiXmlElement *)>("triangle",parseTriangle));
};


CGFobject * ParseANFscene::parseTriangle(TiXmlElement * anfTriangle){
	const char *valString;

	Point3d data[3] = {{0,0,0},{0,0,0},{0,0,0}};

	for(unsigned i = 0; i < 3; i++){

		std::string attr = "xyz" + std::to_string((long double)(i+1));
		valString= anfTriangle->Attribute(attr.c_str());
		if(!valString || !sscanf(valString,"%f %f %f",&data[i].x, &data[i].y, &data[i].z)==3){
			printf("Error! error parsing xyz%d \n",i+1);
			return NULL;
		}
	}
	
	return new Triangle(data);
}

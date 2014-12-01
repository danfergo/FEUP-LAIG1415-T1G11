#include "ANFparser.h"
#include <iostream>
#include <map>
#include <queue>
#include "../scenegraph/primitives/Triangle.h"
#include "../scenegraph/primitives/Retangle.h"
#include "../scenegraph/primitives/Toro.h"
#include "../scenegraph/primitives/Cylinder.h"
#include "../scenegraph/primitives/Sphere.h"
#include "../scenegraph/primitives/Patch.h"
#include "../scenegraph/primitives/Plane.h"
#include "../scenegraph/primitives/Flag.h"
#include "../scenegraph/primitives/Vehicle.h"


void ANFparser::initPrimitiveParsers(){
	
	//insert here all the primitive's parser funcition
	subParsers.insert(std::pair<std::string,PrimitiveParser>("triangle",&ANFparser::parseTriangle));
	subParsers.insert(std::pair<std::string,PrimitiveParser>("rectangle",&ANFparser::parseRetangle));
	subParsers.insert(std::pair<std::string,PrimitiveParser>("cylinder",&ANFparser::parseCylinder));
	subParsers.insert(std::pair<std::string,PrimitiveParser>("torus",&ANFparser::parseToro));
	subParsers.insert(std::pair<std::string,PrimitiveParser>("sphere",&ANFparser::parseSphere));
	subParsers.insert(std::pair<std::string,PrimitiveParser>("patch",&ANFparser::parsePatch));
	subParsers.insert(std::pair<std::string,PrimitiveParser>("vehicle",&ANFparser::parseVehicle));
	subParsers.insert(std::pair<std::string,PrimitiveParser>("flag",&ANFparser::parseFlag));
};


Primitive * ANFparser::parseTriangle(TiXmlElement * anfTriangle){
	const char *valString;

	Point3d data[3] = {{0,0,0},{0,0,0},{0,0,0}};

	for(unsigned i = 0; i < 3; i++){

		std::string attr = "xyz" + std::to_string((long double)(i+1));
		valString= anfTriangle->Attribute(attr.c_str());
		if(!valString || sscanf(valString,"%f %f %f",&data[i].x, &data[i].y, &data[i].z)!=3){
			issue("Error parsing triangle primitive!" + (i+1),WARNING);
			return NULL;
		}
	}

	return new Triangle(data);
}

Primitive * ANFparser::parseRetangle(TiXmlElement * anfRetangle){
	const char *valString;

	Point2d data[2] = {{0,0},{0,0}};

	for(unsigned i = 0; i < 2; i++){

		std::string attr = "xy" + std::to_string((long double)(i+1));
		valString= anfRetangle->Attribute(attr.c_str());
		if(!valString || sscanf(valString,"%f %f",&data[i].x, &data[i].y)!=2){
			issue("Error parsing retangle primitive!" + (i+1),WARNING);
			return NULL;
		}
	}

	return new Retangle(data);
}

Primitive * ANFparser::parseCylinder(TiXmlElement * anfCylinder){
	float base, top, height;
	int stacks, slices;

	if(anfCylinder->QueryFloatAttribute("base", &base) != TIXML_SUCCESS){
		issue("Error parsing Cylinder base attribute.", ERROR);
	}
	if(anfCylinder->QueryFloatAttribute("top", &top) != TIXML_SUCCESS){
		issue("Error parsing Cylinder top attribute.", ERROR);
	}
	if(anfCylinder->QueryFloatAttribute("height", &height) != TIXML_SUCCESS){
		issue("Error parsing Cylinder height attribute.", ERROR);
	}
	if(anfCylinder->QueryIntAttribute("stacks", &stacks) != TIXML_SUCCESS){
		issue("Error parsing Cylinder stacks attribute.", ERROR);
	}
	if(anfCylinder->QueryIntAttribute("slices", &slices) != TIXML_SUCCESS){
		issue("Error parsing Cylinder slices attribute.", ERROR);
	}

	return new Cylinder(scene->getQuadric(),base, top, height, slices, stacks);
}

Primitive * ANFparser::parseSphere(TiXmlElement * anfSphere){
	float radius;
	int stacks, slices;

	if(anfSphere->QueryFloatAttribute("radius", &radius) != TIXML_SUCCESS){
		issue("Error parsing Sphere radius attribute.", ERROR);
	}
	if(anfSphere->QueryIntAttribute("stacks", &stacks) != TIXML_SUCCESS){
		issue("Error parsing Sphere stacks attribute.", ERROR);
	}
	if(anfSphere->QueryIntAttribute("slices", &slices) != TIXML_SUCCESS){
		issue("Error parsing Sphere slices attribute.", ERROR);
	}

	return new Sphere(scene->getQuadric(),radius, stacks, slices);
}

Primitive * ANFparser::parseToro(TiXmlElement * anfToro){
	float inner, outer;
	int slices, loops;

	if(anfToro->QueryFloatAttribute("inner", &inner) != TIXML_SUCCESS){
		issue("Error parsing Sphere radius attribute.", ERROR);
	}
	if(anfToro->QueryFloatAttribute("outer", &outer) != TIXML_SUCCESS){
		issue("Error parsing Toro outer attribute.", ERROR);
	}
	if(anfToro->QueryIntAttribute("slices", &slices) != TIXML_SUCCESS){
		issue("Error parsing Torus slices attribute.", ERROR);
	}
	if(anfToro->QueryIntAttribute("loops", &loops) != TIXML_SUCCESS){
		issue("Error parsing Torus loops attribute.", ERROR);
	}

	return new Toro(inner, outer, slices, loops);
}



/** 
	PROJECT 2 - new primitives
**/

Primitive * ANFparser::parseFlag(TiXmlElement * anfFlag){
	std::string tx = str(anfFlag->Attribute("texture"));
	return new Flag(tx);
}

Primitive * ANFparser::parseVehicle(TiXmlElement * anfVehicle){
	return new Vehicle();
}

Primitive * ANFparser::parsePlane(TiXmlElement * anfPlane){
	int divisions;

	if(anfPlane->QueryIntAttribute("parts", &divisions) != TIXML_SUCCESS){
		issue("Error parsing Vehicle parts attribute.", ERROR);
	}

	return new Plane(divisions);
}

Primitive * ANFparser::parsePatch(TiXmlElement * anfPatch){
	int order;
	float partsU, partsV;
	std::string compute;

	if(anfPatch->QueryIntAttribute("order", &order) != TIXML_SUCCESS){
		issue("Error parsing Vehicle order attribute.", ERROR);
	}
	if(anfPatch->QueryFloatAttribute("partsU", &partsU) != TIXML_SUCCESS){
		issue("Error parsing Vehicle partsU attribute.", ERROR);
	}
	if(anfPatch->QueryFloatAttribute("partsV", &partsV) != TIXML_SUCCESS){
		issue("Error parsing Vehicle partsV attribute.", ERROR);
	}
	
	compute = str(anfPatch->Attribute("compute"));
	
	Patch::Compute comp = Patch::FILL;
	if(compute == "fill"){
		comp = Patch::FILL;
	}else if(compute == "line"){
		comp = Patch::LINE;
	}else if(compute == "point"){
		comp = Patch::POINT;
	}else if(compute == ""){
		issue("Not defined patch value compute attribute. (default value)", WARNING);
	}else{
		issue("Bad value for patch value copmute attribute. (default value)", WARNING);
	}

	Point3d* controlPoints = new Point3d[(order+1)*(order+1)];
	
	TiXmlElement * controlPoint = anfPatch->FirstChildElement("controlpoint");
	int i = 0;
	while(controlPoint){
		float xx, yy, zz;

		if(controlPoint->QueryFloatAttribute("x",&xx) != TIXML_SUCCESS)
			issue("Error parsing coord xx controlpoint patch attribute.", ERROR);
	
		if(controlPoint->QueryFloatAttribute("y",&yy) != TIXML_SUCCESS)
			issue("Error parsing coord yy controlpoint patch attribute.", ERROR);
		
		if(controlPoint->QueryFloatAttribute("z",&zz) != TIXML_SUCCESS)
			issue("Error parsing coord zz controlpoint patch attribute.", ERROR);
	
		controlPoints[i].x = xx; controlPoints[i].y = yy; controlPoints[i].z = zz; 
		controlPoint = controlPoint->NextSiblingElement("controlpoint");
		i++;
	}

	return new Patch(order, partsU, partsV, comp, controlPoints);
}
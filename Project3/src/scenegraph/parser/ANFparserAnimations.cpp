#include "ANFparser.h"
#include "../animations/LinearAnimation.h"
#include <iostream>

void ANFparser::parseAnimations(TiXmlElement * anfAnimations, map<std::string,Animation *> & animations){
	TiXmlElement * anfAnimation = anfAnimations->FirstChildElement("animation");
	Animation * animation;				
	std::string animationId;
	while(anfAnimation){
		animation = NULL;		
		if((animationId = str(anfAnimation->Attribute("id")))!=""){
			if((animation = parseAnimation(anfAnimation))){
				animations.insert(std::pair<std::string,Animation *>(animationId,animation));
			}
		}else{
			issue("Animation id is not defined!. (it will be ignored)",WARNING);
		}

		anfAnimation = anfAnimation->NextSiblingElement("animation");
	}
}


Animation * ANFparser::parseAnimation(TiXmlElement * anfAnimation)
{	
	float span; //tempo que a animacao deve demorar
	std::string id, type;

	id = str(anfAnimation->Attribute("id"));
	if(id == ""){
		issue("Not defined animation id.", ERROR);
	}


	if(anfAnimation->QueryFloatAttribute("span", &span) != TIXML_SUCCESS){
		issue("Error parsing Aniamtion span attribute.", ERROR);
	}

	type = str(anfAnimation->Attribute("type"));
	if(type == "linear"){ //se for movimento linear vai criar uma animacao linear
		
		LinearAnimation * animate = new LinearAnimation(0,span);
		TiXmlElement * controlPoint = anfAnimation->FirstChildElement("controlpoint");
	
		while(controlPoint){
			Point3d newControlPoint;
			float xx, yy, zz;

			if(controlPoint->QueryFloatAttribute("xx",&xx) != TIXML_SUCCESS)
				issue("Error parsing coord xx controlpoint animation attribute.", ERROR);
	
			if(controlPoint->QueryFloatAttribute("yy",&yy) != TIXML_SUCCESS)
				issue("Error parsing coord yy controlpoint animation attribute.", ERROR);
		
			if(controlPoint->QueryFloatAttribute("zz",&zz) != TIXML_SUCCESS)
				issue("Error parsing coord zz controlpoint animation attribute.", ERROR);
	
			newControlPoint.x = xx; newControlPoint.y = yy; newControlPoint.z = zz;
			animate->addControlPoint(newControlPoint);
		
			controlPoint = controlPoint->NextSiblingElement("controlpoint");
		}
	
		return animate;
	} else if(type == "circular"){ //se for movimento circular vai criar uma animacao circular

		float radius, startang, rotang;
		const char * valString;
		Point3d center;

		valString = anfAnimation->Attribute("center");
		if(!valString || sscanf(valString,"%f %f %f",&center.x, &center.y, &center.z)!=3){
			issue("Error parsing center Animation primitive.", ERROR);
		}

		if(anfAnimation->QueryFloatAttribute("radius",&radius) != TIXML_SUCCESS)
			issue("Error parsing radius animation attribute.", ERROR);
		
		if(anfAnimation->QueryFloatAttribute("startang",&startang) != TIXML_SUCCESS)
			issue("Error parsing starang animation attribute.", ERROR);
		
		if(anfAnimation->QueryFloatAttribute("rotang",&rotang) != TIXML_SUCCESS)
			issue("Error parsing rotang animation attribute.", ERROR);
		return new CircularAnimation(0,span, center, radius, startang, rotang);

	} else if(type == ""){
		issue("Not defined animation id.", ERROR);
	} else issue("Not defined animation id.", ERROR);

	issue("Bad animation found", WARNING);
	return NULL;
} 
#include "ANFparser.h"
#include <iostream>
#include <algorithm>

void ANFparser::parseLights(TiXmlElement * anfLights){
	TiXmlElement * anfLight = anfLights->FirstChildElement("light");
	while(anfLight){
		parseLight(anfLight);
		anfLight = anfLight->NextSiblingElement("light");
	}
}

void ANFparser::parseLight(TiXmlElement * anfLight){
	float aa[4],dd[4],ss[4], loc[4], targ[4];
	loc[3] = 1.0;
	bool e=true, m=true, spot=false;
	float angle,exponent;


	std::string titleId = str(anfLight->Attribute("id"));
	if(titleId == ""){
		issue("Not defined id for light. assumed 'unknown' ",WARNING);
		titleId = "uknown";
	}else{
		std::vector<Light *> lights = scene->getLights();
		for(std::vector<Light *>::iterator it = lights.begin(); it != lights.end(); it++){
			if((*it)->getIdTitle() == titleId){
				issue("Light with repeated id.",WARNING);
				break;
			}
		}
	}

	std::string type = str(anfLight->Attribute("type"));
	if(type =="omni" || type=="spot"){

		//location
		const char * location = anfLight->Attribute("pos");
		if(!location || sscanf(location,"%f %f %f ",&loc[0],&loc[1],&loc[2])!=3) {
			issue("Error parsing light location. (Light will be ignored)",WARNING);
			return;
		}

		//enabled
		std::string enabled = str(anfLight->Attribute("enabled"));
		if(enabled == "true" || enabled == "false"){
			e = (enabled == "true") ? true : false;
		}else if (enabled=="") issue("Light enabled attribute not defined. (true will be assumed)",WARNING);
		else issue("Bad value for light enabled attribute. (true will be assumed)",WARNING);

		//marker
		std::string marker = str(anfLight->Attribute("marker"));
		if(marker == "true" || marker == "false"){
			m = (marker == "true") ? true : false;
		}else if (marker=="") issue("Light marker attribute not defined. (true will be assumed)",WARNING);
		else issue("Bad value for light marker attribute. (true will be assumed)",WARNING);


		//is goes wrong exception is thrown
		parseComponent(anfLight,aa,dd,ss);


		if(type=="spot"){ 

			if(anfLight->QueryFloatAttribute("angle",&angle)!=TIXML_SUCCESS){
				issue("Error parsing angle value for spot light. (omni will be assumed)",WARNING);
			}else{

				if(anfLight->QueryFloatAttribute("exponent",&exponent)!=TIXML_SUCCESS){
					issue("Error parsing angle value exponent for spot light. (omni will be assumed)",WARNING);
				}else{
					const char * location = anfLight->Attribute("target");
					if(!location || sscanf(location,"%f %f %f",&targ[0],&targ[1],&targ[2])!=3) {
						issue("Error parsing spot light direction. (omni will be assumed)",WARNING);
					}else{
						// create a spot light
						spot = true;
					}
				}
			}
		}
		// create a omni light
		bool success;
		if(!spot) success = scene->addLight(titleId,aa,dd,ss,e,loc,m,-1,-1,NULL);
		else success = scene->addLight(titleId,aa,dd,ss,e,loc,m,angle,exponent,targ);

		if(!success) issue("Scene can only have 8 lights.This will be ignored.",WARNING);

	}else if (type=="") issue("Light type not defined. Light will be ignored",WARNING);
	else issue("Bad value for light type. Light will be ignored",WARNING);

}
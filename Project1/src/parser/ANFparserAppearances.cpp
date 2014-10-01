#include "ANFparser.h"

void ParseANFscene::parseAppearances(TiXmlElement * anfAppearances, std::map<std::string, CGFappearance *> & appearances){
	TiXmlElement * anfAppearance = anfAppearances->FirstChildElement("appearance");
	CGFappearance  * appearance;
	std::string appeId;
	while(anfAppearance){
		appeId = anfAppearance->Value();
		if(appeId != ""){
			if((appearance=parseAppearance(anfAppearance))){
				appearances.insert(std::pair<std::string,CGFappearance *>(appeId,appearance));
			}
		}else{
			issue("Appearance id is not defined!",WARNING);
		}
		anfAppearance = anfAppearance->NextSiblingElement("appearance"); 
	}
}



CGFappearance * ParseANFscene::parseAppearance(TiXmlElement * anfAppearance){

	TiXmlElement * component = anfAppearance->FirstChildElement("component");
	std::string type;
	const char *val;
	float aa[4],dd[4],ss[4];
	bool a=false,d=false,s=false;

	while(component){
		type = ParseANFscene::str(component->Attribute("type"));
		val = component->Attribute("value");
		if(type == "specular"){ //specular component
			if(s) issue("Component 'specular' of appearance declared more than once. ",WARNING);

			if(!val || sscanf(val,"%f %f %f %f",&ss[0],&ss[1],&ss[2],&ss[3])!=4) 
				issue("Error parsing specular component. ",WARNING);
			else s = true;
		}else if(type=="diffuse"){//diffuse component
			if(s) issue("Component 'diffuse' of appearance declared more than once. ",WARNING); 

			if(!val || sscanf(val,"%f %f %f %f",&dd[0],&dd[1],&dd[2],&dd[3])!=4) 
				issue("Error parsing diffuse component. ",WARNING);
			else d = true;
				
		}else if(type=="ambient"){//ambinent component
			if(s) issue("Component 'ambient' of appearance declared more than once. ",WARNING);

			if(!val || sscanf(val,"%f %f %f %f",&aa[0],&aa[1],&aa[2],&aa[3])!=4) 
				issue("Error parsing ambient component. ",WARNING);
			else a = true;
		}else{
			issue("Bad component type found '"+type+"'!",WARNING);
		}
		component = component->NextSiblingElement("component");
	}

	return new CGFappearance(aa,dd,ss,NULL);
}
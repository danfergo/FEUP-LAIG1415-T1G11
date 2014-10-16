#include "ANFparser.h"
#include <iostream>

void ANFparser::parseAppearances(TiXmlElement * anfAppearances, std::map<std::string, Appearance *> & appearances,
	std::map<std::string, Texture *> & textures){

	TiXmlElement * anfAppearance = anfAppearances->FirstChildElement("appearance");
	Appearance  * appearance;
	std::string appeId;
	while(anfAppearance){
		appeId = str(anfAppearance->Attribute("id"));
		if(appeId != ""){
			
			if((appearance=parseAppearance(anfAppearance,textures))){
				appearances.insert(std::pair<std::string,Appearance *>(appeId,appearance));
			}

		}else{
			issue("Appearance id is not defined!. (it will be ignored)",WARNING);
		}
		anfAppearance = anfAppearance->NextSiblingElement("appearance"); 
	}
}



Appearance * ANFparser::parseAppearance(TiXmlElement * anfAppearance,std::map<std::string, Texture *> & textures){
	float aa[4],dd[4],ss[4],shininess;
	parseComponent(anfAppearance,aa,dd,ss);
	
	if(anfAppearance->QueryFloatAttribute("shininess",&shininess) != TIXML_SUCCESS){
		issue("error parsing texture shininess",ERROR);
	}

	Texture * texture = NULL;
	std::string textureId = str(anfAppearance->Attribute("textureref"));
	if(textureId != ""){
		try{
			texture = textures.at(textureId);
		}catch(...){
			issue("Texture width id='"+textureId+" not found . will not be ignored'.",WARNING);
		}		

	}

	Appearance * appearance = new Appearance(aa,dd,ss,shininess);
	appearance->setTexture(texture);
	return appearance;
}


void ANFparser::parseComponent(TiXmlElement * anfParent, float aa[4], float dd[4], float ss[4]){
		
	TiXmlElement * component = anfParent->FirstChildElement("component");
	std::string type;
	const char *val;
	bool a=false,d=false,s=false;

	while(component){
		type = ANFparser::str(component->Attribute("type"));
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

	if(!s || !a || !d){
		std::string parentname = anfParent->Value();
		issue("One or more components missing from "+parentname+".",ERROR);
	}

}

Texture * ANFparser::parseTexture(TiXmlElement * anfTexture){
	std::string filename;
	if((filename = str(anfTexture->Attribute("file")))==""){
		issue("Texture filename not defined! (texture will be ignored)",WARNING);
		return NULL;
	}

	float s = 1,t = 1;
	if(anfTexture->QueryFloatAttribute("texlength_s",&s) != TIXML_SUCCESS){
		issue("Bad value of texlength_s found! (texture will be ignored)",WARNING);
		return NULL;
	}

	if(anfTexture->QueryFloatAttribute("texlength_t",&t) != TIXML_SUCCESS){
		issue("Bad value of texlength_t found! (texture will be ignored)",WARNING);
		return NULL;
	}
	try{
		return new Texture(filename,s,t);
	}catch(...){
		issue("We couldn't open your texture file: "+ filename +".",WARNING);
		return NULL;
	}
}

void ANFparser::parseTextures(TiXmlElement * anfTextures,map<std::string,Texture *> & textures){
	TiXmlElement * anfTexture = anfTextures->FirstChildElement("texture");
	Texture * texture;				
	std::string textureId;
	while(anfTexture){
		texture = NULL;		
		if((textureId = str(anfTexture->Attribute("id")))!=""){
			if((texture = parseTexture(anfTexture))){
				textures.insert(std::pair<std::string,Texture *>(textureId,texture));
			}
		}else{
			issue("Texture id is not defined!. (it will be ignored)",WARNING);
		}

		anfTexture = anfTexture->NextSiblingElement("texture");
	}
}
#include "ANFparser.h"

#include <iostream>
void ANFparser::parseGlobals(TiXmlElement * anfGlobals){
	// Processing drawing block
	TiXmlElement * anfDrawing = anfGlobals->FirstChildElement("drawing");
	if(anfDrawing){
		parseGlobalsDrawing(anfDrawing);
	}else{
		issue("Globals block 'drawing' no found. (defaults should be assumed)",WARNING);
	}

	// Processing culling block
	TiXmlElement * anfCulling = anfGlobals->FirstChildElement("culling");
	if(anfCulling){
		parseGlobalsCulling(anfCulling);
	}else{
		issue("Globals block 'culling' no found. (defaults should be assumed)",WARNING);
	}

	// Processing lighting block
	TiXmlElement * anfLighting = anfGlobals->FirstChildElement("lighting");
	if(anfDrawing){
		parseGlobalsLighting(anfLighting);
	}else{
		issue("Globals block 'lighting' no found. (defaults should be assumed)",WARNING);
	}


}

void ANFparser::parseGlobalsDrawing(TiXmlElement * anfDrawing){
	std::string mode = str(anfDrawing->Attribute("mode")),
		shading = str(anfDrawing->Attribute("shading"));
	
	//drawing mode
	if(mode == "fill"){
		scene->setDrawingMode(Scene::FILL);
	}else if(mode == "line"){
		scene->setDrawingMode(Scene::LINE);
	}else if(mode == "point"){
		scene->setDrawingMode(Scene::POINT);
	}else if(mode == ""){
		issue("Not defined value for drawing mode.(default assumed)",WARNING);
	}else{
		issue("Bad value for drawing mode.(default assumed)",WARNING);
	}



	//shadding mode
	if(shading == "flat"){
		scene->setShaddingMode(Scene::FLAT);
	}else if(shading == "gouraud"){
		scene->setShaddingMode(Scene::GOURAUD);	
	}else if(shading == ""){
		issue("Not defined value for shadding mode.(default assumed)",WARNING);
	}else{
		issue("Bad value for shadding mode.(default assumed)",WARNING);
	}


	//background color
	float bg[4];
	const char * anfBg = anfDrawing->Attribute("background");
	if(!anfBg || sscanf(anfBg,"%f %f %f %f",&bg[0],&bg[1],&bg[2],&bg[3])!=4) 
		issue("Error parsing globals background color. ",WARNING);
	else 
		scene->setBackgroundColor(bg);
}

void ANFparser::parseGlobalsCulling(TiXmlElement * anfCulling){
	std::string face = str(anfCulling->Attribute("face")),
		order = str(anfCulling->Attribute("order"));

	//culling mode
	if(face == "none"){
		scene->setCullingFace(Scene::NONE);
	}else if(face == "back"){
		scene->setCullingFace(Scene::BACK);
	}else if(face == "front"){
		scene->setCullingFace(Scene::FRONT);
	}else if(face == "both"){
		scene->setCullingFace(Scene::BOTH);
	}else if(face == ""){
		issue("Not defined value for culling face.(default assumed)",WARNING);
	}else{
		issue("Bad value for culling face.(default assumed)",WARNING);
	}

	//drawing order
	if(order == "ccw"){

		scene->setDrawingOrder(Scene::CCW);
	}else if(order == "cw"){
		scene->setDrawingOrder(Scene::CW);
	}else if(order == ""){

		issue("Not defined value for drawing order.(default assumed)",WARNING);
	}else{

		issue("Bad value for drawing order.(default assumed)",WARNING);
						std::cout << "asdajsdçld" << std::endl;
	}

}

void ANFparser::parseGlobalsLighting(TiXmlElement * anfLighting){
	std::string doublesided = str(anfLighting->Attribute("doublesided")),
	local = str(anfLighting->Attribute("local")),
	enabled = str(anfLighting->Attribute("enabled"));

	//drawing doublesided
	if(doublesided == "true"){
		scene->setDoubleSidedEnabled(true);
	}else if(doublesided == "false"){
		scene->setDoubleSidedEnabled(false);
	}else if(doublesided == ""){
		issue("Not defined value for doublesided drawing.(default assumed)",WARNING);
	}else{
		issue("Bad value for doublesided drawing.(default assumed)",WARNING);
	}

	//enable local lighting
	if(local == "true"){
		scene->setLocalIlluminationEnabled(true);
	}else if(local == "false"){
		scene->setLocalIlluminationEnabled(false);
	}else if(local == ""){
		issue("Not defined value for local lighting.(default assumed)",WARNING);
	}else{
		issue("Bad value for local lighting.(default assumed)",WARNING);
	}

	//enable lighting
	if(enabled == "true"){
		scene->setLightingEnabled(true);
	}else if(enabled == "false"){
		scene->setLightingEnabled(false);
	}else if(enabled == ""){
		issue("Not defined value for lighting.(default assumed)",WARNING);
	}else{
		issue("Bad value for drawing lighting.(default assumed)",WARNING);
	}

	//ambient light
	float light[4];
	const char * anfAmb = anfLighting->Attribute("ambient");
	if(!anfAmb || sscanf(anfAmb,"%f %f %f %f",&light[0],&light[1],&light[2],&light[3])!=4) 
		issue("Error parsing global ambient light. ",WARNING);
	else 
		scene->setAmbientLight(light);
}

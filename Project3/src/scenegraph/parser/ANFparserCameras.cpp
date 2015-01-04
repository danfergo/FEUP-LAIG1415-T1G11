#include "ANFparser.h"

#include "../../game/view/GameCamera.h"

void ANFparser::parseCameras(TiXmlElement *anfCameras,std::string initialCamera){
	std::map<std::string,Camera *> tempCameras; 	
	TiXmlElement * anfCamera = anfCameras->FirstChildElement();
	std::string cameraTag,cameraId;
	Camera * camera;
	while(anfCamera){
		camera = NULL;
		cameraTag = str(anfCamera->Value());
		cameraId = str(anfCamera->Attribute("id"));
		
		if(cameraId == ""){
			issue("Each camera must have an id (ignored)" ,WARNING);
			break;
		}	
		if(tempCameras.find(cameraId) != tempCameras.end()){
			issue("There are at least two cameras with the id '"+cameraId +"' (ignored)",WARNING);
			break;
		}

		if(cameraTag == "ortho"){ //process ortho camera
			camera = parseCameraOrtho(anfCamera);
		}else if(cameraTag == "perspective" || cameraTag == "gamecamera"){ //process prespective camera
			camera = parseCameraPrespective(anfCamera);
		}else{ // we've got a problem, sir
			issue("there is no such camera type '" + cameraTag + "'. (ignored!)",WARNING);
		}
			
		if(camera){
			tempCameras.insert(std::pair<std::string,Camera *>(cameraId,camera));	
		}
		 
		anfCamera = anfCamera->NextSiblingElement();
	}

	std::map<std::string,Camera *>::iterator it,it2;
	if((it = tempCameras.find(initialCamera)) == tempCameras.end()){
			issue("Initial camera '"+initialCamera +"' not found! (ignored)",ERROR);
	}else{
		it2  = tempCameras.begin();
		for(;it2!= tempCameras.end(); it2++){
			scene->addCamera((*it2).second);
		}
		scene->setActiveCamera((*it).second);
	}

}


Camera * ANFparser::parseCameraOrtho(TiXmlElement *anfCamera){
	//<ortho id="ss" direction="ee" near="ff" far="ff" left="ff" right="ff" top="ff" bottom="ff" />
	std::string id, ee;
	CameraOrtho::Axis axis;
	float nearr,farr,left,right,top,bottom;
	
	id = str(anfCamera->Attribute("id"));
	
	if(anfCamera->QueryFloatAttribute("near",&nearr) != TIXML_SUCCESS) {
		issue("we've got a problem parsing near attribute", ERROR);
	}

	if(anfCamera->QueryFloatAttribute("far",&farr) != TIXML_SUCCESS) {
		issue("we've got a problem parsing far attribute", ERROR);
	}

	if(anfCamera->QueryFloatAttribute("right",&right) != TIXML_SUCCESS) {
		issue("we've got a problem parsing right attribute", ERROR);
	}

	if(anfCamera->QueryFloatAttribute("left",&left) != TIXML_SUCCESS) {
		issue("we've got a problem parsing left attribute", ERROR);
	}

	if(anfCamera->QueryFloatAttribute("top",&top) != TIXML_SUCCESS) {
		issue("we've got a problem parsing top attribute", ERROR);
	}

	if(anfCamera->QueryFloatAttribute("bottom",&bottom) != TIXML_SUCCESS) {
		issue("we've got a problem parsing bottom attribute", ERROR);
	}

	ee = str(anfCamera->Attribute("direction"));

	if(ee == "x"){
		axis = CameraOrtho::XX;
	}else if(ee == "y"){
		axis = CameraOrtho::YY;
	}else if(ee == "z"){
		axis = CameraOrtho::ZZ;
	}else{
		issue("attribute of orho camera must be x or y or z", ERROR);
	}
	

	return new CameraOrtho(id,nearr,farr,left,right,bottom,top,axis);
}
Camera * ANFparser::parseCameraPrespective(TiXmlElement *anfCamera){
	std::string id;
	float nearr,farr,angle, pos[3],targ[3];
	const char *position, *target;
	id = str(anfCamera->Attribute("id"));
	
	if(anfCamera->QueryFloatAttribute("near",&nearr) != TIXML_SUCCESS) {
		issue("we've got a problem parsing near attribute", ERROR);
	}

	if(anfCamera->QueryFloatAttribute("near",&nearr) != TIXML_SUCCESS) {
		issue("we've got a problem parsing near attribute", ERROR);
	}

	if(anfCamera->QueryFloatAttribute("far",&farr) != TIXML_SUCCESS) {
		issue("we've got a problem parsing far attribute", ERROR);
	}

	position = anfCamera->Attribute("pos");
	if(!position || sscanf(position,"%f %f %f",&pos[0],&pos[1], &pos[2])!=3){
		issue("Error parsing prespective camera position.",ERROR);
		return NULL;
	}

	target = anfCamera->Attribute("target");
	if(!target || sscanf(target,"%f %f %f",&targ[0],&targ[1], &targ[2])!=3){
		issue("Error parsing prespective camera target.",ERROR);
		return NULL;
	}


	if(anfCamera->QueryFloatAttribute("angle",&angle) != TIXML_SUCCESS) {
		issue("we've got a problem parsing angle attribute", ERROR);
	}

	return  (str(anfCamera->Value()) == "gamecamera")? new GameCamera(id,nearr,farr,pos,targ,angle) : new CameraPerspective(id,nearr,farr,pos,targ,angle);
}
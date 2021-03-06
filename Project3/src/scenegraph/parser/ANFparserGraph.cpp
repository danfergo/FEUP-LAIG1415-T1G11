#include "ANFparser.h"
#include <iostream>
#include <queue>


Board * ANFparser::boardFound = NULL;
MenuButton * ANFparser::buttonFound0 = NULL;
MenuButton * ANFparser::buttonFound1 = NULL;
MenuButton * ANFparser::buttonFound2 = NULL;
MenuButton * ANFparser::buttonFound3 = NULL;
Node  * ANFparser::pieceModelFound = NULL;

Node * ANFparser::parseGraph(TiXmlElement * anfGraph,std::map<std::string, Appearance *> & appearances, std::map<std::string, Animation *> & animations){
	// init some local variables
	map<std::string, NodeWrapper> nodeWrappers;
	NodeWrapper nodeWrapper;

	// getting root id
	std::string rootId = str(anfGraph->Attribute("rootid"));
	if(rootId == "") issue("No attribute 'rootid' in 'graph' defined!", ERROR);
	
	// Ok, now lets process all the nodes.
	TiXmlElement *node = anfGraph->FirstChildElement("node");
	std::string nodeId, nodeDispList;
	while(node){
		nodeWrapper = parseNode(node,appearances, animations);
		nodeId = str(node->Attribute("id"));
		if(nodeId == "") issue("Each node must have an id!",ERROR);

		nodeDispList = str(node->Attribute("displaylist"));
		if(nodeDispList == "true"){/*DO SOMETHING WITH display List*/}
		else {/*IGNORE*/}

		if(nodeWrappers.find(nodeId) == nodeWrappers.end()){
			nodeWrappers.insert(std::pair<std::string,NodeWrapper>(nodeId,nodeWrapper));
		}else{	
			issue("Node id's must be unique! '"+ nodeId +"' isn't.",ERROR);
		}
		node=node->NextSiblingElement("node");
	}	

	//We got all the nodes and rootid, lets build the sceneGraph.
	buildSceneGraph(rootId,nodeWrappers);

	return nodeWrappers.at(rootId).node;
} 

ANFparser::NodeWrapper ANFparser::parseNode(TiXmlElement * anfNode, std::map<std::string, Appearance *> & appearances, std::map<std::string, Animation *> & animations){
	// init the return var
	NodeWrapper ret = {new Node(), std::vector<std::string>(), 0}; 

	try {

		// Lets process the transforms block
		TiXmlElement * transforms = anfNode->FirstChildElement("transforms");
		if (transforms == NULL){
			issue("Transforms block not found!",WARNING); 
		}else{
			ANFparser::parseTransforms(ret.node,transforms);
		}

		bool ePrimitives = false, eDescandants = false;

		// Ok, lets process primitives.
		TiXmlElement * primitives = anfNode->FirstChildElement("primitives");
		if (primitives == NULL){
			//issue("Primitives block not found!",WARNING); 
		}else{
			Primitive * primitive;
			TiXmlElement * pr = primitives->FirstChildElement();
			while(pr){
				try{
					if((primitive = (this->*subParsers.at(pr->Value()))(pr))){
						ret.node->addPrimitive(primitive);
						ePrimitives = true;
					}
				}catch(std::out_of_range){
					issue("Invalid primitive '"+str(pr->Value())+"' found!",WARNING);
				}
				pr=pr->NextSiblingElement();
			}
		}


		//checking if node has descendants block
		TiXmlElement * descendants  = anfNode->FirstChildElement("descendants");
		if (descendants == NULL){
			//issue("Block 'descendants' not found!",WARNING);
		}else{
			//lets parse node's descandants then..
			TiXmlElement * ds = descendants->FirstChildElement();
			while(ds){
				if(str(ds->Value()) != "noderef"){
					issue("Invalid block '"+str(ds->Value())+"' found!",WARNING);
				}else if(str(ds->Attribute("id")) == ""){
					issue("Invalid block noderef found. No id set!",WARNING);
				}else{
					ret.descendants.push_back(str(ds->Attribute("id")));
					eDescandants = true;
				}
				ds=ds->NextSiblingElement();
			}
		}

		if(!eDescandants && !ePrimitives)
			issue("Must exist descandants or primitives!",WARNING);

		

		std::string displayList = str(anfNode->Attribute("displaylist"));
		if(displayList == "true") ret.node->setDisplayList();
		else if(displayList != "" && displayList != "false") issue("Bad value found at displaylist attribute", WARNING);



		// lets just apply its appearance before leave
		TiXmlElement * appearanceBlock  = anfNode->FirstChildElement("appearanceref");
		if(appearanceBlock){
			std::string appearanceId = str(appearanceBlock->Attribute("id"));	
			if(appearanceId == "inherit"){
				// nothing needs to be done here.
			}else if(appearanceId != ""){
				try{
					ret.node->setAppearance(appearances.at(appearanceId));
				}catch(...){
					issue("Apperance with id '"+appearanceId+"' not found!",ERROR);
				}
			}else{
				issue("Apperanceref 'id' not defined! ('inherit' could be assumed).",WARNING);
			}
		}else{
			issue("Block 'appearanceref' not found! ('inherit' will be assumed).",WARNING);
		}

		// lets just apply its animation before leave
		TiXmlElement * animationBlock  = anfNode->FirstChildElement("animationref");
		Animation * ani;
		while(animationBlock){
			std::string animationId = str(animationBlock->Attribute("id"));	
			if(animationId != ""){
				try{
					ani = NULL;
					ani = animations.at(animationId);
					if(ani != NULL)ret.node->addAnimation(ani);
				}catch(...){
					issue("Animation with id '"+animationId+"' not found!",ERROR);
				}
			}else{
				issue("Animation 'id' not defined!", ERROR);
			}
			animationBlock = animationBlock->NextSiblingElement("animationref");
		}


		return ret;
	
	}catch(ParseExep & e){
		delete(ret.node); // releasing memory before leave
		throw(e);
	}	
	return ret;
}
/**
Node * ANFparser::parseGraph(TiXmlElement * anfGraph,std::map<std::string, Appearance *> & appearances){
	// init some local variables
	map<std::string, NodeWrapper> nodeWrappers;
	NodeWrapper nodeWrapper;

	// getting root id
	std::string rootId = str(anfGraph->Attribute("rootid"));
	if(rootId == "") issue("No attribute 'rootid' in 'graph' defined!", ERROR);
	
	// Ok, now lets process all the nodes.
	TiXmlElement *node = anfGraph->FirstChildElement("node");
	std::string nodeId;
	while(node){
		nodeWrapper = parseNode(node,appearances);
		nodeId = str(node->Attribute("id"));
		if(nodeId == "") issue("Each node must have an id!",ERROR);

		if(nodeWrappers.find(nodeId) == nodeWrappers.end()){
			nodeWrappers.insert(std::pair<std::string,NodeWrapper>(nodeId,nodeWrapper));
		}else{	
			issue("Node id's must be unique! '"+ nodeId +"' isn't.",ERROR);
		}
		node=node->NextSiblingElement("node");
	}	

	//We got all the nodes and rootid, lets build the sceneGraph.
	buildSceneGraph(rootId,nodeWrappers);

	return nodeWrappers.at(rootId).node;
} 
*/
bool ANFparser::buildSceneGraph(std::string root, map<std::string, ANFparser::NodeWrapper> & nodes){
	//matching node descendantas. here we  also catch bad node's ids and such.
	std::vector<std::string> descendants;
	std::vector<std::string>::iterator it2;
	map<std::string, ANFparser::NodeWrapper>::iterator it = nodes.begin();
	for(;it!= nodes.end(); it++){
			descendants = (*it).second.descendants;
			for(it2 = descendants.begin(); 
				it2 != descendants.end(); it2++){
				try{
					if(*it2 == "option1"){
						(*it).second.node->addDescendants(ANFparser::buttonFound0 = new MenuButton(nodes.at(*it2).node,0));
					}else if(*it2 == "option2"){
						(*it).second.node->addDescendants(ANFparser::buttonFound1 = new MenuButton(nodes.at(*it2).node,1));
					}else if(*it2 == "option3"){
						(*it).second.node->addDescendants(ANFparser::buttonFound2 = new MenuButton(nodes.at(*it2).node,2));
					}else if(*it2 == "option4"){
						(*it).second.node->addDescendants(ANFparser::buttonFound3 = new MenuButton(nodes.at(*it2).node,3));
					}else if(*it2 == "tixel_game_board_piece"){
						(*it).second.node->addDescendants(ANFparser::pieceModelFound = nodes.at(*it2).node);
					}else{
						(*it).second.node->addDescendants(nodes.at(*it2).node);
					}
					nodes.at(*it2).indegree++; // calculating indegree. need in a following verification.
				}catch(...){
					if(*it2 == "tixel_game_board"){
						boardFound = new Board();
						NodeWrapper wrapper = {boardFound, std::vector<std::string>(), 1};
						nodes.insert(std::pair<std::string,NodeWrapper>("tixel_game_board",wrapper));
						(*it).second.node->addDescendants(boardFound);
					}else{
						issue("Node descendant '"+ *it2 + "' not found!",ERROR);
					}
					
				}
			}
	}

	//verifying if root exists and has indegree = 0;
	try{
		if(nodes.at(root).indegree != 0){
			issue("Root can't be a descendant!",ERROR);
		}
		if(!nodes.at(root).node->hasAppearance()){
			issue("Root doesn't has a Appearance. (default gray could be used)",WARNING);
		}
	}catch(...){
		issue("Node root '" + root + "' not found!",ERROR);
	}

	//searching for disconected nodes;
	for(it = nodes.begin();it!= nodes.end(); it++){
		if((*it).second.indegree == 0 && (*it).first != root){
			issue("There is at least one disconnected node. '" + (*it).first + "' is one of them.",ERROR);
		}
	}

	//solvin topological order to check if GraphScene is a DAG.
	// some initializations..
	NodeWrapper node;
	std::queue<NodeWrapper> c, t;
	c.push(nodes.at(root));

	// processing..
	while(!c.empty()){
		node = c.front(); c.pop();
		t.push(node);
		descendants = node.descendants;
		for(it2 = descendants.begin(); it2 != descendants.end(); it2++){
				if((--nodes.at(*it2).indegree) == 0)
					c.push(nodes.at(*it2));
		}
	}
	// the conclusion:
	if(t.size() != nodes.size()){
		issue("Bad node structure found. This structure has cycles.",ERROR);
	}

	return true;
}
/**
ANFparser::NodeWrapper ANFparser::parseNode(TiXmlElement * anfNode,std::map<std::string, Appearance *> & appearances){
	// init the return var
	NodeWrapper ret = {new Node(), std::vector<std::string>(), 0}; 

	try {

		// Lets process the transforms block
		TiXmlElement * transforms = anfNode->FirstChildElement("transforms");
		if (transforms == NULL){
			issue("Transforms block not found!",WARNING); 
		}else{
			ANFparser::parseTransforms(ret.node,transforms);
		}

		bool ePrimitives = false, eDescandants = false;

		// Ok, lets process primitives.
		TiXmlElement * primitives = anfNode->FirstChildElement("primitives");
		if (primitives == NULL){
			//issue("Primitives block not found!",WARNING); 
		}else{
			Primitive * primitive;
			TiXmlElement * pr = primitives->FirstChildElement();
			while(pr){
				try{
					if((primitive = (this->*subParsers.at(pr->Value()))(pr))){
						ret.node->addPrimitive(primitive);
						ePrimitives = true;
					}
				}catch(std::out_of_range){
					issue("Invalid primitive '"+str(pr->Value())+"' found!",WARNING);
				}
				pr=pr->NextSiblingElement();
			}
		}


		//checking if node has descendants block
		TiXmlElement * descendants  = anfNode->FirstChildElement("descendants");
		if (descendants == NULL){
			//issue("Block 'descendants' not found!",WARNING);
		}else{
			//lets parse node's descandants then..
			TiXmlElement * ds = descendants->FirstChildElement();
			while(ds){
				if(str(ds->Value()) != "noderef"){
					issue("Invalid block '"+str(ds->Value())+"' found!",WARNING);
				}else if(str(ds->Attribute("id")) == ""){
					issue("Invalid block noderef found. No id set!",WARNING);
				}else{
					ret.descendants.push_back(str(ds->Attribute("id")));
					eDescandants = true;
				}
				ds=ds->NextSiblingElement();
			}
		}

		if(!eDescandants && !ePrimitives)
			issue("Must exist descandants or primitives!",WARNING);


		std::string displayList = str(anfNode->Attribute("displaylist"));
		if(displayList == "true") ret.node->setDisplayList();
		else if(displayList != "" && displayList != "false") issue("Bad value found at displaylist attribute", WARNING);


		// lets just apply its appearance before leave
		TiXmlElement * appearanceBlock  = anfNode->FirstChildElement("appearanceref");
		if(appearanceBlock){
			std::string appearanceId = str(appearanceBlock->Attribute("id"));	
			if(appearanceId == "inherit"){
				// nothing needs to be done here.
			}else if(appearanceId != ""){
				try{
					ret.node->setAppearance(appearances.at(appearanceId));
				}catch(...){
					issue("Apperance with id '"+appearanceId+"' not found!",ERROR);
				}
			}else{
				issue("Apperanceref 'id' not defined! ('inherit' could be assumed).",WARNING);
			}
		}else{
			issue("Block 'appearanceref' not found! ('inherit' will be assumed).",WARNING);
		}

		return ret;
	
	}catch(ParseExep & e){
		delete(ret.node); // releasing memory before leave
		throw(e);
	}	
	return ret;
}
*/
bool ANFparser::parseTransforms(Node * node, TiXmlElement * anfTransforms){
	TiXmlElement * transform = anfTransforms->FirstChildElement("transform");
	std::string type, axis;
	const char *factor, *to;
	float x,y,z, angle;

	// Parsing the node transformations.
	while(transform){
		type = str(transform->Attribute("type"));

		if(type == "scale"){ // Let's parse a Scaling
			factor = transform->Attribute("factor");
			if(!factor || sscanf(factor,"%f %f %f",&x, &y, &z)!=3){
				issue("Error parsing scaling factor.",ERROR);
			}else node->addScaling(x,y,z);
		
		}else if(type == "translate"){ // Let's parse a Translation
			to = transform->Attribute("to");
			if(!to || sscanf(to,"%f %f %f",&x, &y, &z)!=3){
				issue("Error parsing translate coordinates.",ERROR);
			}else node->addTranslation(x,y,z);
		
		}else if(type == "rotate"){ // Let's parse a Rotation
			axis = str(transform->Attribute("axis"));
			if(transform->QueryFloatAttribute("angle",&angle)!=TIXML_SUCCESS){ // bad angle value
				issue("Bad angle found at rotation transform !",ERROR);
			}else if(!node->addRotation(axis,angle)){ // bad axis value
				issue("Bad axis found at rotation transform !",ERROR);
			}
		}else{ // Must be an invalid transform type.
			issue("Invalid transform type found '" + type + "' !",ERROR); 
		}

		transform = transform->NextSiblingElement("transform");
	}
	return true;
}
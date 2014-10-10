#include "ANFparser.h"
#include <iostream>
#include <queue>

Node * ANFparser::parseGraph(TiXmlElement * anfGraph,std::map<std::string, CGFappearance *> & appearances){
	// init some local variables
	map<std::string, NodeWrapper> nodeWrappers;
	NodeWrapper nodeWrapper;

	// getting root id
	std::string rootId = str(anfGraph->Attribute("rootid"));
	if(rootId == "") issue("No attribute 'rootid' in 'graph' defined!", ERROR);
	
	// Ok, now lets process all the nodes.
	TiXmlElement *node = anfGraph->FirstChildElement();
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
		node=node->NextSiblingElement();
	}	

	//We got all the nodes and rootid, lets build the sceneGraph.
	buildSceneGraph(rootId,nodeWrappers);

	return nodeWrappers.at(rootId).node;
} 

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
					(*it).second.node->addDescendants(nodes.at(*it2).node);
					nodes.at(*it2).indegree++; // calculating indegree. need in a following verification.
				}catch(...){
					issue("Node descendant '"+ (*it).first + "' not found!",ERROR);
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

ANFparser::NodeWrapper ANFparser::parseNode(TiXmlElement * anfNode,std::map<std::string, CGFappearance *> & appearances){
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

		// Ok, lets process primitives.
		TiXmlElement * primitives = anfNode->FirstChildElement("primitives");
		if (primitives == NULL){
			issue("Primitives block not found!",WARNING); 
		}else{
			CGFobject * primitive;
			TiXmlElement * pr = primitives->FirstChildElement();
			while(pr){
				try{
					if((primitive = (this->*subParsers.at(pr->Value()))(pr))){
						ret.node->addPrimitive(primitive);
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
			issue("Block 'descendants' not found!",WARNING);
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
				}
				ds=ds->NextSiblingElement();
			}
		}


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
					issue("Apperance width id '"+appearanceId+"' not found!",ERROR);
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
				issue("Error parsing scaling factor.",WARNING);
			}else node->addScaling(x,y,z);
		
		}else if(type == "translate"){ // Let's parse a Translation
			to = transform->Attribute("to");
			if(!to || sscanf(to,"%f %f %f",&x, &y, &z)!=3){
				issue("Error parsing translate coordinates.",WARNING);
			}else node->addTranslation(x,y,z);
		
		}else if(type == "rotate"){ // Let's parse a Rotation
			axis = str(transform->Attribute("axis"));
			if(transform->QueryFloatAttribute("angle",&angle)!=TIXML_SUCCESS){ // bad angle value
				issue("Bad angle found at rotation transform !",WARNING);
			}else if(!node->addRotation(axis,angle)){ // bad axis value
				issue("Bad axis found at rotation transform !",WARNING);
			}
		}else{ // Must be an invalid transform type.
			issue("Invalid transform type found '" + type + "' !",WARNING); 
		}

		transform = transform->NextSiblingElement("transform");
	}
	return true;
}
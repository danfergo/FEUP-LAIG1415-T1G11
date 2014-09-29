#include "ANFparser.h"
#include <iostream>
#include <map>
#include <queue>

const char ParseANFscene::STRICT = 0;
const char ParseANFscene::PERMISSIVE = 1;
const char ParseANFscene::SILENT = 2;

ParseANFscene::ParseANFscene(const char parseMode): parseMode(parseMode){
	
	//insert here all the primitive's parser funcition
	subParsers.insert(std::pair<std::string,CGFobject* (*)(TiXmlElement *)>("triangle",parseTriangle));
  
}

bool ParseANFscene::parse(Scene * scene,const char* filename){
	TiXmlDocument * doc = new TiXmlDocument(filename);

	//First things first, reading the XML/ANF file
	if (!doc->LoadFile()){
		printf("ERROR! Could not load file '%s'. Error='%s'.", filename, doc->ErrorDesc());
		return false;
	}

	//Must exist anf root block
	TiXmlElement* anfRoot = doc->FirstChildElement("anf");
	if (anfRoot == NULL){
		printf("ERROR! Main block 'anf' block not found! \n");
		return false;
	}

	//If appearances block exist, we call its parser
	TiXmlElement* anfAppearances = anfRoot->FirstChildElement("appearances");
	std::vector<CGFappearance *> appearances;
	if(anfAppearances == NULL){
		printf("ERROR! Block 'appearances' not found! \n");
		return false;
	}else{
		if(!parseAppearances(anfAppearances,appearances)){
			return false;
		}
	}

	//If graph block exist, we call its parser
	TiXmlElement* anfGraph = anfRoot->FirstChildElement("graph");
	if(anfGraph == NULL){
		printf("ERROR! Block 'graph' not found! \n");
		return false;
	}else{
		Node * root = parseGraph(anfGraph);
		if(root != NULL){
			scene->setRoot(root);
		}else{
			return false;
		}
	}

	return true;
}

bool ParseANFscene::parseAppearances(TiXmlElement * anfAppearances, std::vector<CGFappearance *> & appearances){

	return true;
}

Node * ParseANFscene::parseGraph(TiXmlElement * anfGraph){
	// init some local variables
	map<std::string, NodeWrapper> nodeWrappers;
	NodeWrapper nodeWrapper;

	// getting root id
	std::string rootId = std::string(anfGraph->Attribute("rootid"));
	if(rootId == ""){
		printf("ERROR! No attribute 'rootid' in 'graph' found! \n");
		return NULL;
	}
	
	// Ok, now lets process all the nodes.
	TiXmlElement *node = anfGraph->FirstChildElement();
	std::string nodeId;
	while(node){
		nodeWrapper = parseNode(node);
		if(nodeWrapper.node == NULL){
			return NULL;
		}
		nodeId = string(node->Attribute("id"));
		if(nodeId == ""){
			printf("ERROR! Each node must have an id! \n");
			return NULL;
		}

		if(nodeWrappers.find(nodeId) == nodeWrappers.end()){
			nodeWrappers.insert(std::pair<std::string,NodeWrapper>(nodeId,nodeWrapper));
		}else{
			std::cout << "ERROR! Node id's must be unique! '"<< nodeId <<"' isn't. \n";
			return NULL;
		}
		node=node->NextSiblingElement();
	}	

	//We got all the nodes and rootid, lets build the sceneGraph.
	if(!buildSceneGraph(rootId,nodeWrappers)){
		return NULL;
	}
	return nodeWrappers.at(rootId).node;
} 

bool ParseANFscene::buildSceneGraph(std::string root, map<std::string, ParseANFscene::NodeWrapper> & nodes){
	//matching node descendantas. here we  also catch bad node's ids and such.
	std::vector<std::string> descendants;
	std::vector<std::string>::iterator it2;
	map<std::string, ParseANFscene::NodeWrapper>::iterator it = nodes.begin();
	for(;it!= nodes.end(); it++){
			descendants = (*it).second.descendants;
			for(it2 = descendants.begin(); 
				it2 != descendants.end(); it2++){
				try{
					(*it).second.node->addDescendants(nodes.at(*it2).node);
					nodes.at((*it2)).indegree++; // calculating indegree. need in a following verification.
				}catch(...){
					printf("ERROR! Node descendant '%s' not found! \n", (*it).first);
					return false;
				}
			}
	}

	//verifying if root exists and has indegree = 0;
	try{
		if(nodes.at(root).indegree != 0){
			printf("ERROR! Root can't be a descendant! \n");
			return false;
		}
	}catch(...){
		std::cout <<"ERROR! Node root '"<< root<< "' not found! \n";
		return false;
	}

	//searching for disconected nodes;
	for(it = nodes.begin();it!= nodes.end(); it++){
		if((*it).second.indegree == 0 && (*it).first != root){
			std::cout << "ERROR! There is at least one disconnected node. '" << (*it).first << "' is one of them. \n";
			return false;
		}
	}

	//solvin topological order to check if GraphScene is a DAG.
	// some initializations..
	NodeWrapper node;
	std::queue<NodeWrapper> c, t;
	c.push(nodes.at(root));

	// processing...
	while(!c.empty()){
		node = c.front(); c.pop();
		t.push(node);
		descendants = node.descendants;
		for(it2 = descendants.begin(); it2 != descendants.end(); it2++){
				if((--nodes.at(*it2).indegree) == 0)
					t.push(nodes.at(*it2));
		}
	}
	// the conclusion
	if(t.size() != nodes.size()){
			std::cout<< "ERROR! Bad node structure found. This structure has cycles. \n";
			return false;
	}

	return true;
}

ParseANFscene::NodeWrapper ParseANFscene::parseNode(TiXmlElement * anfNode){
	
	// init the return var
	NodeWrapper ret = {new Node(), std::vector<std::string>(), 0}; 
	

	// Check if node has transforms  block
	TiXmlElement * transforms = anfNode->FirstChildElement("transforms");
	if (transforms == NULL){
		printf("WARNING! Transforms block not found! \n"); 
		goto failreturn;
	}

	if(!ParseANFscene::parseTransforms(ret.node,transforms)){
		goto failreturn;
	}

	// Check if node has primitives block
	TiXmlElement * primitives = anfNode->FirstChildElement("primitives");
	if (primitives == NULL){
		printf("WARNING! Primitives block not found! \n"); 
		goto failreturn;
	}

	// Ok, lets process each primitive then.
	CGFobject * primitive;
	TiXmlElement * pr = primitives->FirstChildElement();
	while(pr){
		try{
			if((primitive = subParsers.at(pr->Value())(pr)) == NULL)
				goto failreturn;
			ret.node->addPrimitive(primitive);
		}catch(...){
			printf("WARNING! Invalid primitive '%s' found! \n",pr->Value());
			goto failreturn;
		}
		pr=pr->NextSiblingElement();
	}
	
	//checking if node has descendants block
	TiXmlElement * descendants  = anfNode->FirstChildElement("descendants");
	if (descendants == NULL){
		printf("WARNING! Block 'descendants' not found! \n");
		goto failreturn;
	}

	//lets parse node's descandants then..
	TiXmlElement * ds = descendants->FirstChildElement();
	while(ds){
		if(std::string(ds->Value()) != "noderef"){
			printf("WARNING! Invalid block '%s' found! \n",ds->Value());
			goto failreturn;
		}else if(std::string(ds->Attribute("id")) == ""){
			printf("WARNING! Invalid block noderef found. No id set! \n");
			goto failreturn;
		}else{
			ret.descendants.push_back(std::string(ds->Attribute("id")));
		}
		ds=ds->NextSiblingElement();
	}

	return ret;

failreturn:
	delete(ret.node); ret.node = NULL;
	return ret;
}

bool ParseANFscene::parseTransforms(Node * node, TiXmlElement * anfTransforms){
	TiXmlElement * transform = anfTransforms->FirstChildElement("transform");
	std::string type, axis;
	const char *factor, *to;
	float x,y,z, angle;

	// Parsing the node transformations.
	while(transform){
		type = std::string(transform->Attribute("type"));
		
		if(type == "scale"){ // Let's parse a Scaling
			factor = transform->Attribute("factor");
			if(!factor || !sscanf(factor,"%f %f %f",&x, &y, &z)==3){
				printf("Error! error parsing scaling factor \n");
				return false;
			}
			node->addScaling(x,y,z);
		}else if(type == "translate"){ // Let's parse a Translation
			to = transform->Attribute("to");
			if(!to || !sscanf(to,"%f %f %f",&x, &y, &z)==3){
				printf("Error! error parsing scaling factor \n");
				return false;
			}
			node->addTranslation(x,y,z);
		}else if(type == "rotate"){ // Let's parse a Rotation
			axis = std::string(transform->Attribute("axis"));
			transform->QueryFloatAttribute("angle",&angle);
			/*if(!){ // bad angle value
				printf("WARNING! Bad angle found at rotation transform ! \n");
				return false;
			}else */if(!node->addRotation(axis,angle)){ // bad axis value
				printf("WARNING! Bad axis found at rotation transform ! \n");
				return false;
			}
		}else{ // Must be an invalid transform type.
			std::cout << "WARNING! Invalid transform type found '" << type << "' ! \n"; 
			return false;
		}
		transform = transform->NextSiblingElement("transform");
	}
	return true;
}

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


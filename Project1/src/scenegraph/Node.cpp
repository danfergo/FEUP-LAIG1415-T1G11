#include "Node.h"

#include <iostream>

Node::Node()
{
}


Node::~Node()
{
}

void Node::addPrimitive(CGFobject * primitive){
	this->primitives.push_back(primitive);
}

void Node::addDescendants(Node * descendant){
	this->descendants.push_back(descendant);
}

void Node::processNode(CGFappearance * parentAppearance){
	glPushMatrix();
		// ok lets apply this node transformations
		//glMulMatrix(transformations);
		
		// we are going to draw this node's primitives
		for(std::vector<CGFobject *>::iterator it = primitives.begin();
			it != primitives.end(); it++){
				(*it)->draw();
		}

		//now we process this node's descandents
		for(std::vector<Node *>::iterator it = descendants.begin(); it != descendants.end(); it++){
			(*it)->processNode(NULL);
		}

	glPopMatrix();
}

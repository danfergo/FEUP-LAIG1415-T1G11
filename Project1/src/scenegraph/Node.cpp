#include "Node.h"

#include <iostream>

Node::Node()
{
	transforms.identity();
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
		glMultMatrixf(transforms.get());
		
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



void Node::addRotationX(float angle){
	transforms.rotate(angle, 1,0,0);  
}

void Node::addRotationY(float angle){
	transforms.rotate(angle, 0,1,0); 
}

void Node::addRotationZ(float angle){
	transforms.rotate(angle, 0,0,1); 
}

void Node::addScaling(float x, float y, float z){
	transforms.scale(x,y,z); 
}

void Node::addTranslation(float x, float y, float z){
	transforms.translate(x, y, z);
}

#include "Node.h"

#include <iostream>

Node::Node():appearance(NULL)
{
	for(unsigned i=0; i<16; i++)
		transforms[i] = (i%5 == 0) ? 1 : 0 ;
}


Node::~Node()
{
	/*CGFobject * pri;
	while(primitives.size()){
		pri = primitives.back();
		primitives.pop_back();
		std::cout << "xalskdasjdl" << std::endl;
		delete pri;
	}

	Node * desc;
	while(descendants.size()){
		desc = descendants.back();
		descendants.pop_back();
		delete desc;
	}*/

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
		glMultMatrixf(transforms);
		
		// before draw anything lets apply 
		CGFappearance * currentAppearance = this->appearance?this->appearance: parentAppearance;
		if(currentAppearance != NULL)currentAppearance->apply();

		// we are going to draw this node's primitives
		for(std::vector<CGFobject *>::iterator it = primitives.begin();
			it != primitives.end(); it++){
				(*it)->draw();
		}

		//now we process this node's descendants
		for(std::vector<Node *>::iterator it = descendants.begin(); it != descendants.end(); it++){
			(*it)->processNode(currentAppearance);
		}

	glPopMatrix();
}

void Node::addRotationX(float angle){
	glLoadMatrixf(transforms);
	glRotatef(angle, 1,0,0);

	glGetFloatv(GL_MODELVIEW_MATRIX, transforms);
}

void Node::addRotationY(float angle){
	glLoadMatrixf(transforms);
	glRotatef(angle, 0,1,0);
	glGetFloatv(GL_MODELVIEW_MATRIX, transforms);
}

void Node::addRotationZ(float angle){
	glLoadMatrixf(transforms);
	glRotatef(angle, 0,0,1);
	glGetFloatv(GL_MODELVIEW_MATRIX, transforms); 
}

void Node::addScaling(float x, float y, float z){
	glLoadMatrixf(transforms);
	glScalef(x,y,z);
	glGetFloatv(GL_MODELVIEW_MATRIX, transforms); 
}

void Node::addTranslation(float x, float y, float z){
	glLoadMatrixf(transforms);
	glTranslatef(x, y, z);
	glGetFloatv(GL_MODELVIEW_MATRIX, transforms);
}

bool Node::addRotation(std::string axis, float angle){
	if(axis == "xx"){
		addRotationX(angle);
	}else if(axis == "yy"){
		addRotationY(angle);
	}else if(axis == "zz"){
		addRotationZ(angle);
	}else{
		return false;	
	}	
	return true;
}


void Node::setAppearance(CGFappearance * appearance){
	delete(this->appearance);
	this->appearance = appearance;
}

bool Node::hasAppearance()  const{
	return appearance!=NULL;
};
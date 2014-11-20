#include "Node.h"

#include <iostream>

Node::Node():appearance(NULL),displayListId(-1), isDisplayList(false)
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

void Node::addPrimitive(Primitive * primitive){
	this->primitives.push_back(primitive);
}

void Node::addDescendants(Node * descendant){
	this->descendants.push_back(descendant);
}

void Node::processNodeInitialization(Appearance * parentAppearance){


	// we visit all the descendants and initialize it,
	for(std::vector<Node *>::iterator it = descendants.begin(); it != descendants.end(); it++){
		(*it)->processNodeInitialization(parentAppearance);
	}

	// now we can "record" the display list relative to this node. 
	// if any descendant is a display list then, it should be already recorded and, 
	// it should be called during this node recording.
	if(displayListId == 0){
		int displayListId = glGenLists(1);
		glNewList(displayListId,GL_COMPILE);
			processNode(parentAppearance);
			this->displayListId = displayListId;
		glEndList();
	}
}




void Node::processNode(Appearance * parentAppearance){
	
		if(displayListId > 0){
			glCallList(displayListId);
			return;
		}
		
		glPushMatrix();
			// ok lets apply this node transformations
			glMultMatrixf(transforms);
		

			// before draw anything lets apply
			Appearance * currentAppearance = this->appearance ? this->appearance: parentAppearance;
			if(currentAppearance != NULL)currentAppearance->apply();

			glPushMatrix();
				for(std::vector<Animation *>::iterator it = animations.begin(); it != animations.end(); it++)
					(*it)->animate();

				// we are going to draw this node's primitives
				for(std::vector<Primitive *>::iterator it = primitives.begin();
					it != primitives.end(); it++){
						(*it)->draw(currentAppearance ? currentAppearance->getTexture() : NULL);
				}

				//now we process this node's descendants
				for(std::vector<Node *>::iterator it = descendants.begin(); it != descendants.end(); it++){
					(*it)->processNode(currentAppearance);
				}
			glPopMatrix();
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
	if(axis == "x"){
		addRotationX(angle);
	}else if(axis == "y"){
		addRotationY(angle);
	}else if(axis == "z"){
		addRotationZ(angle);
	}else{
		return false;	
	}	
	return true;
}


void Node::setAppearance(Appearance * appearance){
	delete(this->appearance);
	this->appearance = appearance;
}

bool Node::hasAppearance()  const{
	return appearance!=NULL;
};


void Node::setDisplayList(){
	if(displayListId < 0) displayListId = 0;
}


void Node::addAnimation(Animation * animation){
	animations.push_back(animation->clone(getLastAnimationEndTime()));
}

unsigned  Node::getLastAnimationEndTime() const{
	if(animations.size() == 0) return 0;
	return animations.back()->getEndTime();	
}

void Node::update(unsigned time){
	for(std::vector<Animation *>::iterator it = animations.begin(); it != animations.end(); it++)
		(*it)->update(time);

	for(std::vector<Node *>::iterator it  = descendants.begin(); it != descendants.end(); it++)
		(*it)->update(time);

}

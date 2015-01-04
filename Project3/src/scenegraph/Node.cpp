#include "Node.h"

#include <iostream>

Node::Node():appearance(NULL),isDisplayList(false),currentAnimationIndex(0),lastEndTime(0), name(0), touchable(false), visible(true)
{
	this->resetTransformations();
}

Node::Node(Primitive * primitive):appearance(NULL),isDisplayList(false),currentAnimationIndex(0),lastEndTime(0), name(0), touchable(false), visible(true){
	this->resetTransformations();
	this->addPrimitive(primitive);
}

Node::~Node() { 

}

void Node::addPrimitive(Primitive * primitive){
	this->primitives.push_back(primitive);
}

void Node::addDescendants(Node * descendant){
	this->descendants.push_back(descendant);
}

void Node::processNodeInitialization(Appearance * parentAppearance){
	
	Appearance * currentAppearance = this->appearance ? this->appearance: parentAppearance;
	

	// we visit all the descendants and initialize it,
	for(std::vector<Node *>::iterator it = descendants.begin(); it != descendants.end(); it++){
		(*it)->processNodeInitialization(currentAppearance);
	}

	// now we can "record" the display list relative to this node. 
	// if any descendant is a display list then, it should be already recorded and, 
	// it should be called during this node recording.

	if(isDisplayList){
		try{
			displayListsIds.at(currentAppearance); // tries to find displayList with parentAppearance
		}catch(...){ 
			int dspId = glGenLists(1);
			glNewList(dspId,GL_COMPILE);
				processNode(parentAppearance,true,false, 0);
				displayListsIds.insert(std::pair<Appearance *,int>(currentAppearance,dspId));
			glEndList();
		}
	}
}


void Node::processNode(Appearance * parentAppearance, bool parentIsVisible, bool parentIsTouchable, std::vector<Node *> * nodes){
		bool callAnimationCallback = false;
		Appearance * currentAppearance = this->appearance ? this->appearance: parentAppearance;
		bool currentTouchable = (parentIsTouchable || this->touchable);
		bool currentVisible = (parentIsVisible && this->visible);
		float temp[16], matrix[16];
		if(isDisplayList){
			try{
				int id = this->displayListsIds.at(currentAppearance); 
				glCallList(id);
				return;
			}catch(...){
				/** continue and draw it . **/ 
			}
		}
		

		if(nodes != NULL && this->touchable){ 
			glPushName(nodes->size()); 
			nodes->push_back(this); 
		}
		glPushMatrix();
			
			// ok lets apply this node transformations
			glMultMatrixf(transforms);

			// before draw anything lets apply
			if(currentAppearance != NULL)currentAppearance->apply();

			glPushMatrix();
				//for(std::vector<Animation *>::iterator it = animations.begin(); it != animations.end(); it++)
				/** if(animations.size() > 0) animations[currentAnimationIndex]->animate(); **/
				for(std::vector<Animation *>::iterator it = animations.begin(); it != animations.end(); ){
					(*it)->getTransformationMatrix(matrix);
					glMultMatrixf(matrix);
					if((*it)->complete()){	
						glGetFloatv(GL_MODELVIEW_MATRIX, temp);
						glLoadMatrixf(transforms);
						glMultMatrixf(matrix);
						glGetFloatv(GL_MODELVIEW_MATRIX, transforms); 
						glLoadMatrixf(temp);

						delete *it;
						it = animations.erase(it);
						if(animations.size() == 0) 	callAnimationCallback = true;
					}else{
						it++;
					}
				}
					

				// we are going to draw this node's primitives
				if((nodes == NULL && currentVisible) || (nodes != NULL && currentTouchable)){
					for(std::vector<Primitive *>::iterator it = primitives.begin();
						it != primitives.end(); it++){
							(*it)->draw(currentAppearance ? currentAppearance->getTexture() : NULL);
					}
				}

				//now we process this node's descendants
				for(std::vector<Node *>::iterator it = descendants.begin(); it != descendants.end(); it++){
					(*it)->processNode(currentAppearance,currentVisible,currentTouchable,nodes);
				}
				
			glPopMatrix();
			
		glPopMatrix();
		if(nodes != NULL  && this->touchable){ 
			glPopName(); 
		}

		if(callAnimationCallback) animationCallback();
}

void Node::addRotationX(float angle){
	float temp[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, temp);
		glLoadMatrixf(transforms);
		glRotatef(angle, 1,0,0);
		glGetFloatv(GL_MODELVIEW_MATRIX, transforms);
	glLoadMatrixf(temp);
}

void Node::addRotationY(float angle){
	float temp[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, temp);
		glLoadMatrixf(transforms);
		glRotatef(angle, 0,1,0);
		glGetFloatv(GL_MODELVIEW_MATRIX, transforms);
	glLoadMatrixf(temp);
}

void Node::addRotationZ(float angle){
	float temp[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, temp);
		glLoadMatrixf(transforms);
		glRotatef(angle, 0,0,1);
		glGetFloatv(GL_MODELVIEW_MATRIX, transforms); 
	glLoadMatrixf(temp);
}

void Node::addScaling(float x, float y, float z){
	float temp[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, temp);
		glLoadMatrixf(transforms);
		glScalef(x,y,z);
		glGetFloatv(GL_MODELVIEW_MATRIX, transforms); 
	glLoadMatrixf(temp);
}

void Node::addTranslation(float x, float y, float z){
	float temp[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, temp);
		glLoadMatrixf(transforms);
		glTranslatef(x, y, z);
		glGetFloatv(GL_MODELVIEW_MATRIX, transforms);
	glLoadMatrixf(temp);
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
	//if(displayListId < 0) displayListId = 0;
	isDisplayList = true;
}


void Node::addAnimation(Animation * animation){
	/** animation->clone(getLastAnimationEndTime()) **/
	animations.push_back(animation);
}

unsigned  Node::getLastAnimationEndTime() const{
	if(animations.size() == 0) return 0;
	return animations.back()->getEndTime();	
}

void Node::update(unsigned time){
	for(std::vector<Animation *>::iterator it = animations.begin(); it != animations.end(); it++)
		(*it)->update(time);
	/**
	if(time == 0){
		 currentAnimationIndex = 0;
		if(animations.size() > 0) lastEndTime = animations[0]->getEndTime();
	}
	else if(time > lastEndTime && (currentAnimationIndex+1) < animations.size()){
		currentAnimationIndex++;
		lastEndTime = animations[currentAnimationIndex]->getEndTime();
	}
	
	if(animations.size() > 0){
		animations[currentAnimationIndex]->update(time);
	}

	**/ 
	for(std::vector<Node *>::iterator it  = descendants.begin(); it != descendants.end(); it++)
		(*it)->update(time);

}


void Node::setTouchable(bool t){
	this->touchable = t;
}

void Node::setVisible(bool visible){
	this->visible = visible;
}

bool Node::clickHandler(){
	return true;
}

void Node::resetTransformations(){
	for(unsigned i=0; i<16; i++)
		transforms[i] = (i%5 == 0) ? 1 : 0 ;
}
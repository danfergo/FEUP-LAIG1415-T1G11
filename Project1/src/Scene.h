#ifndef SCENE_H
#define SCENE_H

#include "CGFscene.h"
#include "scenegraph/Node.h"

class Scene : public CGFscene
{
private:
	Node * root;
public:
	void init();
	void display();
	void setRoot(Node * root);
}; 

#endif
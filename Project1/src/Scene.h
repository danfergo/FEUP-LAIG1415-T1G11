#ifndef SCENE_H
#define SCENE_H

#include "CGFscene.h"
#include "scenegraph/Node.h"

class Scene : public CGFscene
{
private:
	
public:
	Node * root;
	void init();
	void display();
}; 

#endif
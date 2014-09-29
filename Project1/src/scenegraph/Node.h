#pragma once
#include "CGFobject.h"
#include "CGFappearance.h"
#include <vector>
#include "Matrices.h"

class Node
{
private:
	std::vector<Node *> descendants;
	std::vector<CGFobject *> primitives;
	float transforms[16];
public:
	Node();
	~Node();
	void processNode(CGFappearance * parentAppearance);
	void addPrimitive(CGFobject * primitive);
	void Node::addDescendants(Node * descendant);

	bool addRotation(std::string axis, float angle);
	void addRotationX(float angle);
	void addRotationY(float angle);
	void addRotationZ(float angle);
	void addScaling(float x, float y, float z);
	void addTranslation(float x, float y, float z);

};


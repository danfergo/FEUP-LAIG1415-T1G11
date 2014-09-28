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
	Matrix4 transforms;
public:
	Node();
	~Node();
	void processNode(CGFappearance * parentAppearance);
	void addPrimitive(CGFobject * primitive);
	void Node::addDescendants(Node * descendant);

	void addRotationX(float angle);
	void addRotationY(float angle);
	void addRotationZ(float angle);
	void addScaling(float x, float y, float z);
	void addTranslation(float x, float y, float z);
};


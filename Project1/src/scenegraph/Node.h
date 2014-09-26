#pragma once
#include "CGFobject.h"
#include "CGFappearance.h"
#include <vector>

class Node
{
private:
	std::vector<Node *> descendants;
	std::vector<CGFobject *> primitives;

public:
	Node();
	~Node();
	void processNode(CGFappearance * parentAppearance);
	void addPrimitive(CGFobject * primitive);
	void Node::addDescendants(Node * descendant);
};

